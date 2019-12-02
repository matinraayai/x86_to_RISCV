#include "../include/elfparse.h"
#include <stdio.h>

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
    char* current = malloc(2 * sizeof(char));
    for (unsigned long i = 0; i < elf64.s_hdr[14].sh_size; i++) {
        sprintf(current, "%02hhx", elf64.sect[14][i]);
        printf("%02hhx", elf64.sect[14][i]);
        if ((i + 1) % 4 == 0) {
            printf(" ");
        }
        if ( (i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    free(current);
    free_elf_file(&elf64);
    return 0;
}