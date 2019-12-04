#include <elfparse.h>
#include <stdio.h>
#include <inttypes.h>
#include <Zydis/Zydis.h>
#include <Zydis/Decoder.h>
#include <rvcontext.h>


int main(int argc, char* argv[]) {
    Elf64_t x86elf = elfInit(argv[1], stdout, stderr);
    RVContext rv_context;
    rvContextInit(&rv_context, &x86elf, stderr);
    printSectionHeaders(&x86elf, &rv_context);
    printProgramHeaders(&x86elf);

    // Initialize decoder context
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
    // Initialize formatter. Only required when you actually plan to do instruction
    // formatting ("disassembling"), like we do here
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

    const ZyanUSize window = 15;
    ZydisDecodedInstruction instruction;

    while (rvContextEndOfExecution(&rv_context)) {
        if (!ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, rv_context.inst_ptr, window, &instruction))) {
            fprintf(stderr, "Failed to decode the instruction at address %016" PRIX64, rv_context.rip_s7);
        }
        char buffer[256];

        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer),
                                        rv_context.rip_s7);
        puts(buffer);
        rvContextExecute(&rv_context, &instruction, &x86elf, stderr);
    }
    elfDestroy(&x86elf);
    return 0;
}