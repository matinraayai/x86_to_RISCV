#include <elfparse.h>

Elf64_t initElfFile(char* path, FILE* out_str, FILE* err_str) {
    Elf64_t elf64;
    int elf_file;
    fprintf(out_str, "Opening the ELF binary at %s...\n", path);
    if ((elf_file = open(path, O_RDONLY | O_SYNC, 0)) == -1) {
        fprintf(err_str, "Couldn't find/open the ELF file at %s", path);
        exit(1);
    }
    fprintf(out_str, "Successful.\n");
    elf64.fd = elf_file;
    return elf64;
}

void checkElfFile(Elf64_t* elf64, FILE* out_str, FILE* err_str) {
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
        fprintf(out_str, "ELF binary check passed.\n");
        return;
    }
    else {
        fprintf(err_str, "ELF binary check failed.\n");
        exit(1);
    }
}

void initElfHeader(Elf64_t* elf64) {
    elf64->hdr = malloc(sizeof(Elf64_Ehdr));
    lseek(elf64->fd, (off_t)0, SEEK_SET);
    read(elf64->fd, (void *)(elf64->hdr), sizeof(Elf64_Ehdr));
}

void initElfProgramHeaderTables(Elf64_t* elf64) {
    Elf64_Ehdr* elf_header = elf64->hdr;
    Elf64_Phdr* p_header_table = malloc(elf_header->e_phnum * elf_header->e_phentsize);
    lseek(elf64->fd, (off_t) elf_header->e_phoff, SEEK_SET);
    for (int i = 0; i < elf_header->e_phnum; i++) {
        read(elf64->fd, (void *)&p_header_table[i], elf_header->e_phentsize);
    }
    elf64->p_hdr = p_header_table;
}

void initElfSectionHeaderTables(Elf64_t* elf64) {
    Elf64_Ehdr* elf_header = elf64->hdr;
    Elf64_Shdr* sec_header_table = malloc(elf_header->e_shnum * elf_header->e_shentsize);
    lseek(elf64->fd, (off_t) elf_header->e_shoff, SEEK_SET);
    for (int i = 0; i < elf_header->e_shnum; i++) {
        read(elf64->fd, (void *)&sec_header_table[i], elf_header->e_shentsize);
    }
    elf64->s_hdr = sec_header_table;
}

void initElfSectionNames(Elf64_t* elf64) {
    int e_shstrndx = elf64->hdr->e_shstrndx;
    Elf64_Shdr* s_hdr_table = elf64->s_hdr;
    elf64->s_names = malloc(s_hdr_table[e_shstrndx].sh_size);
    lseek(elf64->fd, (off_t) s_hdr_table[e_shstrndx].sh_offset, SEEK_SET);
    read(elf64->fd, (void *) (elf64->s_names), s_hdr_table[e_shstrndx].sh_size);
}

Elf64_t elfInit(char* path, FILE* out_str, FILE* err_str) {
    Elf64_t elf64 = initElfFile(path, out_str, err_str);
    initElfHeader(&elf64);
    checkElfFile(&elf64, out_str, err_str);
    initElfProgramHeaderTables(&elf64);
    initElfSectionHeaderTables(&elf64);
    initElfSectionNames(&elf64);
    return elf64;
}

void elfDestroy(Elf64_t* elf64) {
    close(elf64->fd);
    free(elf64->hdr);
    free(elf64->s_hdr);
    free(elf64->s_names);
}


void printSectionHeaders(Elf64_t* elf64)
{
    uint32_t i;
    Elf64_Shdr* sh_table = elf64->s_hdr;
    Elf64_Ehdr* eh = elf64->hdr;
    unsigned char* sh_str = (unsigned char*) elf64->s_names;
    /* Read section-header string-table */
    printf("========================================");
    printf("========================================\n");
    printf(" idx offset     load-addr  size       algn"
           " flags      type       section\n");
    printf("========================================");
    printf("========================================\n");
    for(i=0; i<eh->e_shnum; i++) {
        printf(" %03d ", i);
        printf("0x%08lx ", sh_table[i].sh_offset);
        printf("0x%08lx ", sh_table[i].sh_addr);
        printf("0x%08lx ", sh_table[i].sh_size);
        printf("%4lu ", sh_table[i].sh_addralign);
        printf("0x%08lx ", sh_table[i].sh_flags);
        printf("0x%08ux ", sh_table[i].sh_type);
        printf("%s", (sh_str + sh_table[i].sh_name));
        printf("\n");
    }
    printf("========================================");
    printf("========================================\n");
    printf("\n");	/* end of section header table */
}

void printProgramHeaders(Elf64_t* elf64)
{
    uint32_t i;
    Elf64_Phdr* ph_table = elf64->p_hdr;
    Elf64_Ehdr* eh = elf64->hdr;
    printf("========================================");
    printf("========================================\n");
    printf(" idx offset     virt-addr  phy-addr       type"
           " Memsize    FileSize      Flags\n");
    printf("========================================");
    printf("========================================\n");
    for(i=0; i<eh->e_phnum; i++) {
        printf(" %03d ", i);
        printf("0x%08lx ", ph_table[i].p_offset);
        printf("0x%08lx ", ph_table[i].p_vaddr);
        printf("0x%08lx ", ph_table[i].p_paddr);
        printf("%4d ", ph_table[i].p_type);
        printf("0x%08lx ", ph_table[i].p_memsz);
        printf("0x%08lx ", ph_table[i].p_filesz);
        printf("0x%08x ", ph_table[i].p_flags);
        printf("\n");
    }
    printf("========================================");
    printf("========================================\n");
    printf("\n");	/* end of section header table */
}




