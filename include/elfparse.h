/**
 * This file was written with help from https://github.com/TheCodeArtist/elf-parser and the Linux man page.
 */
#ifndef ELFPARSE_H
#define ELFPARSE_H
#include <elf.h>
#include <stdbool.h>
#include <zconf.h>
#include <stdlib.h>

void read_header(int fd, Elf64_Ehdr *elf_header);

bool check_magic_elf_bytes(Elf64_Ehdr *elf_header);

unsigned char get_elf_binary_arch(Elf64_Ehdr *elf_header);

unsigned char get_elf_data_encoding(Elf64_Ehdr *elf_header);

unsigned char get_elf_os_abi_version(Elf64_Ehdr *elf_header);

unsigned char get_elf_target_machine(Elf64_Ehdr *elf_header);

void read_all_section_header_tables(int fd, Elf64_Ehdr *elf_header, Elf64_Shdr *sec_header_table);

char* read_section(int fd, Elf64_Shdr *section_header);

char* read_all_elf_sections(int fd, Elf64_Ehdr *elf_header, Elf64_Shdr *sec_header_table);
#endif //ELFPARSE_H
