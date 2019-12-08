#include <elfparse.h>
#include <stdio.h>
#include <inttypes.h>
#include <Zydis/Zydis.h>
#include <Zydis/Decoder.h>
#include <rvcontext.h>
#define INST_WINDOW_SIZE 15

int main(int argc, char* argv[]) {
    Elf64_t x86elf = elf64_tInit(argv[1], stdout, stderr);
    RVContext rv_context = rvContextInit(&x86elf, stdout, stderr);

    // Initializing decoder context, formatter and instruction.
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);
    const ZyanUSize window = INST_WINDOW_SIZE;
    ZydisDecodedInstruction instruction;

    // Main execution loop:
    printf("Starting execution:\n");
    printf("========================================================================================\n");
    while (!rvContextEndOfExecution(&rv_context)) {
        //Decode the x86 instruction.
        if (!ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, rv_context.rip_s7 + rv_context.mem, window, &instruction))) {
            fprintf(stderr, "Failed to decode the instruction at address %016" PRIX64, rv_context.rip_s7);
            exit(-1);
        }
        printf("%016" PRIX64 "  ", rv_context.rip_s7);
        char buffer[256];
        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer),
                                        rv_context.rip_s7);
        puts(buffer);
        rvContextExecute(&rv_context, &instruction, stderr);
    }
    printf("Execution end reached.\n");
    printf("========================================================================================\n");
    rvContextPrint(&rv_context, stdout);
    //Program cleanup:
    rvContextDestroy(&rv_context);
    elf64_tDestroy(&x86elf);
    return 0;
}