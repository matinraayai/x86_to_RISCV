#include <stdio.h>
#include <fcntl.h>
#include "../include/elfparse.h"

int main(int argc, char* argv[]) {
    int elf_file;
    Elf64_Ehdr elf_header;
    if ((elf_file = open(argv[1], O_RDONLY | O_SYNC, 0)) == -1) {
        printf("Couldn't open the file.");
        return -1;
    }
    read_header(elf_file, &elf_header);
    printf("Are ELF magic bits present: %s\n", check_magic_elf_bytes(&elf_header) ? "True": "False");
    printf("Is the ELF binary architecture 64 bit?: %s", get_elf_binary_arch(&elf_header) == ELFCLASS64
    ? "True": "False");
    return 0;
}