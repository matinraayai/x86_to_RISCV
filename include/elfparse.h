/**
 * This file was written with help from https://github.com/TheCodeArtist/elf-parser and the Linux man page.
 */
#ifndef ELFPARSE_H
#define ELFPARSE_H
#include <elf.h>
#include <stdbool.h>
#include <zconf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


typedef struct elf_t_ {
    int             fd; // File descriptor associated with the elf.
    Elf64_Ehdr*     hdr; // Header table.
    Elf64_Phdr*     p_hdr; // Program header table.
    Elf64_Shdr*     s_hdr; // Section header table.
    char**          sect; // All Sections combined.
} Elf64_t;

Elf64_t read_elf_file(char* path, FILE* out_str, FILE* err_str);

void initialize_elf_header(Elf64_t* elf64);

void check_elf(Elf64_t* elf64, FILE* out_str, FILE* err_str);

void read_section_header_tables(Elf64_t* elf64);

Elf64_t init_elf_file(char* path, FILE* out_str, FILE* err_str);

void free_elf_file(Elf64_t* elf64);

#endif //ELFPARSE_H
