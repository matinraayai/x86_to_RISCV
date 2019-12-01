#include "../include/elfparse.h"


/**
 * Reads in the header of the elf file associated with the file descriptor into the given Elf64_Ehdr pointer.
 * @param fd the file descriptor for the elf file.
 * @param elf_header a pointer to the output elf_header data structure.
 */
void initialize_elf_header(const int fd, Elf64_Ehdr *elf_header) {
    lseek(fd, (off_t)0, SEEK_SET);
    read(fd, (void *)elf_header, sizeof(Elf64_Ehdr));
}

/**
 * Checks the first 4 characters of the ELF header.
 * @param elf_header the desired Elf64_Ehdr data structure.
 * @return True if all the bytes are correct, False otherwise.
 */
bool check_magic_elf_bytes(Elf64_Ehdr *elf_header) {
    return (elf_header->e_ident[EI_MAG0] == ELFMAG0) &&
           (elf_header->e_ident[EI_MAG1] == ELFMAG1) &&
           (elf_header->e_ident[EI_MAG2] == ELFMAG2) &&
           (elf_header->e_ident[EI_MAG3] == ELFMAG3);
}

unsigned char get_elf_binary_arch(Elf64_Ehdr *elf_header) {
    return elf_header->e_ident[EI_CLASS];
}

unsigned char get_elf_data_encoding(Elf64_Ehdr *elf_header) {
    return elf_header->e_ident[EI_DATA];
}

unsigned char get_elf_os_abi_version(Elf64_Ehdr *elf_header) {
    return elf_header->e_ident[EI_OSABI];
}

unsigned char get_elf_target_machine(Elf64_Ehdr *elf_header) {
    return elf_header->e_machine;
}

Elf64_Shdr* read_all_section_header_tables(int fd, Elf64_Ehdr *elf_header) {
    Elf64_Shdr* sec_header_table = malloc(elf_header->e_shnum * elf_header->e_shentsize);
    lseek(fd, (off_t) elf_header->e_shoff, SEEK_SET);
    for (int i = 0; i < elf_header->e_shnum; i++) {
        read(fd, (void *)&sec_header_table[i], elf_header->e_shentsize);
    }
    return sec_header_table;
}

char** read_all_elf_sections(int fd, Elf64_Ehdr *elf_header, Elf64_Shdr *sec_header_table) {
    char** all_sections = malloc(elf_header->e_shnum * sizeof(char*));
    for (int i = 0; i < elf_header->e_shnum; i++) {
        all_sections[i] = malloc(sec_header_table[i].sh_size);
        lseek(fd, (off_t) sec_header_table[i].sh_offset, SEEK_SET);
        read(fd, (void *)all_sections[i], sec_header_table[i].sh_size);
    };
    return all_sections;
}

char* read_section(int fd, Elf64_Shdr *section_header) {
    char* out = malloc(section_header->sh_size);
    lseek(fd, (off_t)section_header->sh_offset, SEEK_SET);
    read(fd, (void *)out, section_header->sh_size);
    return out;
}

