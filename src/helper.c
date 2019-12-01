#include "../include/helper.h"


int read_elf_file(char* path) {
    int elf_file;
    printf("Opening the ELF binary...\n");
    if ((elf_file = open(path, O_RDONLY | O_SYNC, 0)) == -1) {
        printf("Couldn't open the file.\n");
        exit(1);
    }
    printf("Successful.\n");
    return elf_file;
}

void check_elf_header(Elf64_Ehdr *elf_header) {
    printf("Checking the ELF file...\n");
    bool magic_status = check_magic_elf_bytes(elf_header);
    printf("Are ELF magic bits present: %s\n", magic_status ? "True": "False");
    bool bin_arch = (get_elf_binary_arch(elf_header) == ELFCLASS64);
    printf("Is the ELF binary architecture 64 bit?: %s\n", bin_arch ? "True": "False");
    bool os_abi = (get_elf_os_abi_version(elf_header) == ELFOSABI_SYSV) || (get_elf_os_abi_version(elf_header) == ELFOSABI_LINUX);
    printf("Is the ELF binary's target OS Unix or Linux?: %s\n", os_abi ? "True": "False");
    bool machine_arch = (get_elf_target_machine(elf_header) == EM_X86_64);
    printf("Is the ELF binary's target ISA AMD x86_64? %s\n", machine_arch ? "True": "False");
    if (magic_status && bin_arch && os_abi && machine_arch) {
        printf("ELF binary check passed.\n");
        return;
    }
    else {
        printf("ELF binary check failed.\n");
        exit(1);
    }
}