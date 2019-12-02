#include <elfparse.h>
#include <stdio.h>
#include <inttypes.h>
#include <Zydis/Zydis.h>
#include <Zydis/Decoder.h>


void print_section_headers(Elf64_t* elf64)
{
    uint32_t i;
    Elf64_Shdr* sh_table = elf64->s_hdr;
    Elf64_Ehdr* eh = elf64->hdr;
    char* sh_str = (elf64->sect)[eh->e_shstrndx];
    /* Read section-header string-table */
    printf("========================================");
    printf("========================================\n");
    printf(" idx offset     load-addr  size       algn"
           " flags      type       section\n");
    printf("========================================");
    printf("========================================\n");
    for(i=0; i<eh->e_shnum; i++) {
        printf(" %03d ", i);
        printf("0x%08x ", sh_table[i].sh_offset);
        printf("0x%08x ", sh_table[i].sh_addr);
        printf("0x%08x ", sh_table[i].sh_size);
        printf("%4d ", sh_table[i].sh_addralign);
        printf("0x%08x ", sh_table[i].sh_flags);
        printf("0x%08x ", sh_table[i].sh_type);
        //sh_str = read_section(fd, &sh_table[eh->e_shstrndx]);
        printf("%s\t", (sh_str + sh_table[i].sh_name));
        printf("\n");
    }
    printf("========================================");
    printf("========================================\n");
    printf("\n");	/* end of section header table */
}

int main(int argc, char* argv[]) {
    Elf64_t elf64 = init_elf_file(argv[1], stdout, stderr);
    print_section_headers(&elf64);
    ZyanU8* data = elf64.sect[14];

    // Initialize decoder context
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);

    // Initialize formatter. Only required when you actually plan to do instruction
    // formatting ("disassembling"), like we do here
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

    // Loop over the instructions in our buffer.
    // The runtime-address (instruction pointer) is chosen arbitrary here in order to better
    // visualize relative addressing
    ZyanU64 runtime_address = elf64.s_hdr[14].sh_addr;
    ZyanUSize offset = 0;
    const ZyanUSize length = 15;
    ZydisDecodedInstruction instruction;
    while (offset < elf64.s_hdr[14].sh_size) {
        ZyanStatus stat =
        ZydisDecoderDecodeBuffer(&decoder, data + offset, length, &instruction);
        printf("%016" PRIX64 "  ", runtime_address);
        char buffer[256];
        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer),
                                        runtime_address);
        puts(buffer);
        offset += instruction.length;
        runtime_address += instruction.length;
    }

//    while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, data + offset, length - offset, &instruction)))
//    {
//        // Print current instruction pointer.
//        printf("%016" PRIX64 "  ", runtime_address);
//
//        // Format & print the binary instruction structure to human readable format
//        char buffer[256];
//        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer),
//                                        runtime_address);
//        puts(buffer);
//
//        offset += instruction.length;
//        runtime_address += instruction.length;
//    }

    free_elf_file(&elf64);
    return 0;
}