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
    char*           s_names; // For keeping track of section names.
    Elf64_Sym*      sym_tbl; // For keeping track of symbols in the program.
    char*           sym_names; // For keeping track of symbol names.
    uint32_t        sym_count; // For keeping track of number of symbols.
} Elf64_t;

/**
 * Initializes an Elf64_t structure using its path on disk.
 * @param path to the elf file on disk.
 * @param out_str output stream for progress indication.
 * @param err_str error stream for error diagnostics.
 * @return an initialized Elf64_t structure.
 */
Elf64_t elf64_tInit(char* path, FILE* out_str, FILE* err_str);

/**
 * Deallocates all the resources of elf64 and closes the elf file associated with it.
 * @param elf64 reference to the Elf64_t struct.
 */
void elf64_tDestroy(Elf64_t* elf64);

#endif //ELFPARSE_H
