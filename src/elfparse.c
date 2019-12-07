#include <elfparse.h>


/**
 * Initializes the file descriptor field inside the passed Elf64_t* reference.
 * Exits the program upon failure.
 * @param elf64 the Elf64_t reference.
 * @param path to the elf file.
 * @param out_str the output stream for showing progress.
 * @param err_str the error stream for printing any errors.
 */
void initElfFile(Elf64_t* elf64, char* path, FILE* out_str, FILE* err_str) {
    int elf_file;
    fprintf(out_str, "Opening the ELF binary at %s...\n", path);
    if ((elf_file = open(path, O_RDONLY | O_SYNC, 0)) == -1) {
        fprintf(err_str, "Couldn't find/open the ELF file at %s", path);
        exit(-1);
    }
    fprintf(out_str, "Successfully opened the elf file.\n");
    elf64->fd = elf_file;
}

/**
 * Verifies the elf file to be an x86_64 Linux executable using the bits present in the header.
 * Exits the program upon failure.
 * @param elf64 the Elf64_t struct reference representing the elf file.
 * @param out_str output stream for printing the progress.
 * @param err_str error stream for printing any errors.
 */
void verifyElfFile(Elf64_t* elf64, FILE* out_str, FILE* err_str) {
    Elf64_Ehdr* elf_header = elf64->hdr;
    fprintf(out_str, "Checking the ELF file...\n");
    bool magic_bytes = (elf_header->e_ident[EI_MAG0] == ELFMAG0) &&
                       (elf_header->e_ident[EI_MAG1] == ELFMAG1) &&
                       (elf_header->e_ident[EI_MAG2] == ELFMAG2) &&
                       (elf_header->e_ident[EI_MAG3] == ELFMAG3);
    fprintf(out_str, "Are ELF magic bits present: %s\n", magic_bytes ? "True": "False");

    bool bin_arch = (elf_header->e_ident[EI_CLASS] == ELFCLASS64);
    fprintf(out_str, "Is the ELF binary architecture 64 bit?: %s\n", bin_arch ? "True": "False");

    bool endian = (elf_header->e_ident[EI_DATA] == ELFDATA2LSB);
    fprintf(out_str, "Is the ELF binary 2's complement little endian?: %s\n", endian ? "True": "False");

    bool os_abi = (elf_header->e_ident[EI_OSABI] == ELFOSABI_SYSV) || (elf_header->e_ident[EI_OSABI] == ELFOSABI_LINUX);
    fprintf(out_str, "Is the ELF binary's target OS Unix or Linux?: %s\n", os_abi ? "True": "False");

    bool machine_arch = (elf_header->e_machine == EM_X86_64);
    fprintf(out_str, "Is the ELF binary's target ISA AMD x86_64? %s\n", machine_arch ? "True": "False");

    if (magic_bytes && bin_arch && endian && os_abi && machine_arch) {
        fprintf(out_str, "ELF binary verification passed.\n");
        return;
    }
    else {
        fprintf(err_str, "ELF binary verification failed.\n");
        exit(-1);
    }
}

/**
 * Initializes the header structure of the Elf64_t structure by reading the contents of the elf file.
 * Exits the program if it fails to allocate memory or read the header from the elf file.
 * @param elf64 the Elf64_t struct reference representing the elf file.
 * @param out_str output stream to show progress.
 * @param err_str error stream for failure report.
 */
void initElfHeader(Elf64_t* elf64, FILE* out_str, FILE* err_str) {
    fprintf(out_str, "Initializing the elf header...\n");

    elf64->hdr = malloc(sizeof(Elf64_Ehdr));
    if (elf64->hdr == NULL) {
        fprintf(err_str, "Failed to allocate memory for the elf header.\n");
        exit(-1);
    }

    if (lseek(elf64->fd, (off_t)0, SEEK_SET) != (off_t)0) {
        fprintf(err_str, "Failed to seek to the beginning of the file.\n");
        exit(-1);
    }

    if (read(elf64->fd, (void *)(elf64->hdr), sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        fprintf(err_str, "Failed to read the program header from disk.\n");
        exit(-1);
    }
    fprintf(out_str, "Header initialization complete.\n");
}

/**
 * Initializes the program headers table using the elf file in elf64.
 * @param elf64 the Elf64_t reference represnting the elf file.
 * @param out_str output stream for progress indication.
 * @param err_str error stream for error diagnostics.
 */
void initElfProgramHeadersTable(Elf64_t* elf64, FILE* out_str, FILE* err_str) {
    fprintf(out_str, "Initializing the program header section...\n");
    Elf64_Ehdr* elf_header = elf64->hdr;
    Elf64_Phdr* p_header_table = malloc(elf_header->e_phnum * elf_header->e_phentsize);
    if (p_header_table == NULL) {
        fprintf(err_str, "Failed to allocate memory for the program header.\n");
        exit(-1);
    }
    if (lseek(elf64->fd, (off_t) elf_header->e_phoff, SEEK_SET) != (off_t) (elf_header->e_phoff)) {
        fprintf(err_str, "Failed to seek the file descriptor to the program header.\n");
        exit(-1);
    }
    for (int i = 0; i < elf_header->e_phnum; i++) {
        if (read(elf64->fd, (void *)&p_header_table[i], elf_header->e_phentsize) != sizeof(Elf64_Phdr)) {
            fprintf(err_str, "Failed to read the %d-th program header from file.\n", i);
            exit(-1);
        }
    }
    elf64->p_hdr = p_header_table;
    fprintf(out_str, "Program header initialization complete.\n");
}

/**
 * Initializes the section headers table in elf64 from the elf file on disk.
 * @param elf64 the Elf64_t reference to the x86 elf structure.
 * @param out_str output stream for showing progress.
 * @param err_str error stream for error diagnostics.
 */
void initElfSectionHeadersTable(Elf64_t* elf64, FILE* out_str, FILE* err_str) {
    fprintf(out_str, "Initializing the section headers table...\n");
    Elf64_Ehdr* elf_header = elf64->hdr;
    Elf64_Shdr* sec_header_table = malloc(elf_header->e_shnum * elf_header->e_shentsize);
    if (sec_header_table == NULL) {
        fprintf(err_str, "Failed to allocate memory for section headers table.\n");
        exit(-1);
    }
    if (lseek(elf64->fd, (off_t) elf_header->e_shoff, SEEK_SET) != (off_t) (elf_header->e_shoff)) {
        fprintf(err_str, "Failed to seek to the beginning of the headers section on the elf file.\n");
        exit(-1);
    }
    for (int i = 0; i < elf_header->e_shnum; i++) {
        if (read(elf64->fd, (void *)&sec_header_table[i], elf_header->e_shentsize) != sizeof(Elf64_Shdr)) {
            fprintf(err_str, "Failed to read the %d-th section header from the elf file.\n", i);
            exit(-1);
        }
    }
    elf64->s_hdr = sec_header_table;
    fprintf(out_str, "Section headers table initialized.\n");
}

/**
 * Loads the contents of the section header that contains the name of all other sections into the elf64 struct.
 * @param elf64 reference to the Elf64_t.
 * @param out_str output stream for progress tracking.
 * @param err_str error stream for error diagnostics.
 */
void initElfSectionNames(Elf64_t* elf64, FILE* out_str, FILE* err_str) {
    fprintf(out_str, "Initializing the section names string...\n");
    int e_shstrndx = elf64->hdr->e_shstrndx;
    Elf64_Shdr* s_hdr_table = elf64->s_hdr;
    elf64->s_names = malloc(s_hdr_table[e_shstrndx].sh_size);
    if (elf64->s_names == NULL) {
        fprintf(err_str, "Failed to allocate memory for the section name string.\n");
        exit(-1);
    }

    Elf64_Off sec_offset = s_hdr_table[e_shstrndx].sh_offset;
    if(lseek(elf64->fd, (off_t) sec_offset, SEEK_SET) != (off_t) (sec_offset)) {
        fprintf(err_str, "Failed to seek to the section name string in the elf file.\n");
        exit(-1);
    }

    if(read(elf64->fd, (void *) (elf64->s_names), s_hdr_table[e_shstrndx].sh_size) != s_hdr_table[e_shstrndx].sh_size) {
        fprintf(err_str, "Failed to read the section name string from the elf file.\n");
        exit(-1);
    }
    fprintf(out_str, "Section name string initialization complete.\n");
}

/**
 * Prints statistics regarding the section headers to the output stream.
 * @param elf64 reference to an Elf64_t.
 * @param out_str Output stream for the statistics.
 */
void printSectionHeaders(Elf64_t* elf64, FILE* out_str)
{
    Elf64_Shdr* sh_table = elf64->s_hdr;
    Elf64_Ehdr* eh = elf64->hdr;
    unsigned char* sh_str = (unsigned char*) elf64->s_names;
    /* Read section-header string-table */
    fprintf(out_str, "\nSection headers statistics:\n\n");
    fprintf(out_str, "========================================================================================\n");
    fprintf(out_str, " idx offset     load-addr  size       algn flags      type       section\n");
    fprintf(out_str, "========================================================================================\n");
    for(int i=0; i < eh->e_shnum; i++) {
        fprintf(out_str, " %03d ", i);
        fprintf(out_str, "0x%08lx ", sh_table[i].sh_offset);
        fprintf(out_str, "0x%08lx ", sh_table[i].sh_addr);
        fprintf(out_str, "0x%08lx ", sh_table[i].sh_size);
        fprintf(out_str, "%4lu ", sh_table[i].sh_addralign);
        fprintf(out_str, "0x%08lx ", sh_table[i].sh_flags);
        fprintf(out_str, "0x%08u ", sh_table[i].sh_type);
        fprintf(out_str, "%s", (sh_str + sh_table[i].sh_name));
        fprintf(out_str, "\n");
    }
    fprintf(out_str, "========================================================================================\n");
}

//void print_symbols(Elf64_t *elf64)
//{
//    for(int i = 0; i < elf64->hdr->e_shnum; i++) {
//        if ((sh_table[i].sh_type==SHT_SYMTAB)
//            || (sh_table[i].sh_type==SHT_DYNSYM)) {
//            printf("\n[Section %03d]", i);
//            print_symbol_table(fd, eh, sh_table, i);
//        }
//    }
//}

/**
 * Initializes an Elf64_t structure using its path on disk.
 * @param path to the elf file on disk.
 * @param out_str output stream for progress indication.
 * @param err_str error stream for error diagnostics.
 * @return an initialized Elf64_t structure.
 */
Elf64_t initElf64_t(char* path, FILE* out_str, FILE* err_str) {
    Elf64_t elf64;
    initElfFile(&elf64, path, out_str, err_str);
    initElfHeader(&elf64, out_str, err_str);
    verifyElfFile(&elf64, out_str, err_str);
    initElfProgramHeadersTable(&elf64, out_str, err_str);
    initElfSectionHeadersTable(&elf64, out_str, err_str);
    initElfSectionNames(&elf64, out_str, err_str);
    printSectionHeaders(&elf64, out_str);
    return elf64;
}

/**
 * Deallocates all the resources of elf64 and closes the elf file associated with it.
 * @param elf64 reference to the Elf64_t struct.
 */
void elfDestroy(Elf64_t* elf64) {
    free(elf64->hdr);
    free(elf64->s_hdr);
    free(elf64->s_names);
    close(elf64->fd);
}



