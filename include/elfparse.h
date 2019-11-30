/**
 * This file was written with help from https://github.com/TheCodeArtist/elf-parser and the Linux man page.
 */
#ifndef ELFPARSE_H
#define ELFPARSE_H
#include <elf.h>
#include <stdbool.h>

void read_header(int fd, Elf64_Ehdr *elf_header);

bool check_magic_elf_bytes(Elf64_Ehdr *elf_header);

char get_elf_binary_arch(Elf64_Ehdr *elf_header);

char get_elf_data_encoding(Elf64_Ehdr *elf_header);

char get_elf_os_abi_version(Elf64_Ehdr *elf_header);

char get_elf_target_machine(Elf64_Ehdr *elf_header);

#endif //ELFPARSE_H
