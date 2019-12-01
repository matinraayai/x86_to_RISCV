#include <stdio.h>

#include "../include/helper.h"

void print_section_headers(int fd, Elf64_Ehdr* eh, Elf64_Shdr* sh_table, char*** all_sec)
{
    uint32_t i;

    /* Read section-header string-table */
    char* sh_str = (*all_sec)[eh->e_shstrndx];
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
        printf("%d ", sh_table[i].sh_size);
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
    int elf_file = read_elf_file(argv[1]);
    Elf64_Ehdr elf_header;
    initialize_elf_header(elf_file, &elf_header);
    check_elf_header(&elf_header);
    Elf64_Shdr *sec_header_tables = read_all_section_header_tables(elf_file, &elf_header);
    char** all_sections = read_all_elf_sections(elf_file, &elf_header, sec_header_tables);
    print_section_headers(elf_file, &elf_header, sec_header_tables, &all_sections);
    close(elf_file);
    return 0;
}