#include "../include/elfparse.h"

void read_header(int fd, Elf64_Ehdr *elf_header) {
    lseek(fd, (off_t)0, SEEK_SET);
    read(fd, (void *)elf_header, sizeof(Elf64_Ehdr));
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

void read_all_section_header_tables(int fd, Elf64_Ehdr *elf_header, Elf64_Shdr *sec_header_table) {
    lseek(fd, (off_t) elf_header->e_shoff, SEEK_SET);
    for (int i = 0; i < elf_header->e_shoff; i++) {
        read(fd, (void *)&sec_header_table[i], elf_header->e_shentsize)
    }
}

char* read_section(int fd, Elf64_Shdr *section_header) {
    char* out = malloc(section_header->sh_size);
    lseek(fd, (off_t)section_header->sh_offset, SEEK_SET);
    read(fd, (void *)buff, section_header->sh_size);
    return out;
}