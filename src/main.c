#include <elfparse.h>
#include <stdio.h>
#include <inttypes.h>
#include <Zydis/Zydis.h>
#include <Zydis/Decoder.h>
#include <encoder.h>


int main(int argc, char* argv[]) {
    Elf64_t x86elf = elfInit(argv[1], stdout, stderr);
    printSectionHeaders(&x86elf);
    RVContext rv_context;
    rvContextInit(&rv_context, &x86elf, stderr);

    ZyanU8* data = x86elf.sect[14];

    // Initialize decoder context
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
    // Initialize formatter. Only required when you actually plan to do instruction
    // formatting ("disassembling"), like we do here
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);


    ZyanU64 runtime_address = x86elf.s_hdr[14].sh_addr;
    ZyanUSize pc = 0;
    const ZyanUSize window = 15;
    ZydisDecodedInstruction instruction;
    while (pc < x86elf.s_hdr[14].sh_size) {
        if (!ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, data, window, &instruction))) {
            fprintf(stderr, "Failed to decode the instruction at address %016" PRIX64, runtime_address);
        }
        printf("%016" PRIX64 "  ", runtime_address);
        char buffer[256];
        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer),
                                        runtime_address);
        puts(buffer);
        pc += instruction.length;
        data += instruction.length;
        runtime_address += instruction.length;
    }
    elfDestroy(&x86elf);
    return 0;
}