/**
 * Contains all the functions needed for the main routine.
 */
#ifndef HELPER_H
#define HELPER_H
#include <fcntl.h>
#include <stdio.h>
#include "../include/elfparse.h"
/**
 * Reads in the elf file in the given path. Takes care of error checking.
 * @param path
 * @return
 */
int read_elf_file(char* path);

void check_elf_header(Elf64_Ehdr *elf_header);

#endif //HELPER_H
