#include "../include/elfparse.h"

void read_header(int fd, Elf64_Ehdr *elf_header) {

}

bool check_magic_elf_bytes(Elf64_Ehdr *elf_header) {
    return (elf_header->e_ident[EI_MAG0] == ELFMAG0) &&
           (elf_header->e_ident[EI_MAG1] == ELFMAG1) &&
           (elf_header->e_ident[EI_MAG2] == ELFMAG2) &&
           (elf_header->e_ident[EI_MAG3] == ELFMAG3);
}

char get_elf_binary_arch(Elf64_Ehdr *elf_header) {
    return elf_header->e_ident[EI_CLASS];
}

char get_elf_data_encoding(Elf64_Ehdr *elf_header) {
    return elf_header->e_ident[EI_DATA]
}

char get_elf_os_abi_version(Elf64_Ehdr *elf_header) {
    return elf_header->e_ident[EI_OSABI];
}

char get_elf_target_machine(Elf64_Ehdr *elf_header) {
    return elf_header->e_machine;
}
