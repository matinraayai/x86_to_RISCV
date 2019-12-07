/**
 * Header file for handling x86_64 elf files.
 * This file and its src were written with help from https://github.com/TheCodeArtist/elf-parser and the Linux man page.
 */
#ifndef ELFPARSE_H
#define ELFPARSE_H
#include <elf.h>
#include <stdbool.h>
#include <zconf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <Zydis/Status.h>
#include <string.h>

typedef struct {
    int             fd; // File descriptor associated with the elf.
    Elf64_Ehdr*     hdr; // Header table.
    Elf64_Phdr*     p_hdr; // Program header table.
    Elf64_Shdr*     s_hdr; // Section header table.
    ZyanU8*         s_names; // For keeping track of section names.
} Elf64_t;

Elf64_t initElf64_t(char* path, FILE* out_str, FILE* err_str);

void elfDestroy(Elf64_t* elf64);

#endif //ELFPARSE_H
