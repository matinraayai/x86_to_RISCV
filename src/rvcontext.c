#include <rvcontext.h>


void rvContextInit(RVContext* rv_context, Elf64_t* elf64, FILE* err_str) {
    //Find the address of the text segment and put it into the pc.
    rv_context->rip_s7 = elf64->hdr->e_entry;
    rv_context->inst_ptr = rv_context->mem + rv_context->rip_s7;
    //Initialize memory.
    rvContextInitMemory(rv_context, elf64, 1024);

}

void rvContextInitMemory(RVContext *rv_context, Elf64_t* elf64, ZyanUSize stack_mem) {
    Elf64_Ehdr* elf_header = elf64->hdr;
    Elf64_Shdr* s_hdr_table = elf64->s_hdr;
    ZyanUSize mem_size = 0;
    //TODO: If a better way to do this is found, replace this.
    for (int i = elf_header->e_shnum - 1; i > -1; i--) {
        if (s_hdr_table[i].sh_addr > 0) {
            mem_size = s_hdr_table[i].sh_addr + s_hdr_table[i].sh_size;
            break;
        }
    }
    rv_context->mem = malloc(mem_size + stack_mem);
    rv_context->rbp_fp = rv_context->rsp_sp = (ZyanU64) mem_size;
    ////
    for (int i = 0; i < elf_header->e_shnum; i++) {
        ZyanUSize target_addr = s_hdr_table[i].sh_addr;
        lseek(elf64->fd, (off_t) s_hdr_table[i].sh_offset, SEEK_SET);
        read(elf64->fd, (void *) (rv_context->mem + target_addr), s_hdr_table[i].sh_size);
    }
}

void rvContextExecute(RVContext* rv_context, ZydisDecodedInstruction* instruction, Elf64_t* elf64, FILE* err_str) {
    rv_context->inst_ptr += instruction->length;
    rv_context->rip_s7 += instruction->length;
}

bool rvContextEndOfExecution(RVContext* rv_context) {
    return rv_context->gp == rv_context->rip_s7;
}

//For debugging.
void printSectionHeaders(Elf64_t* elf64, RVContext* rv_context)
{
    uint32_t i;
    Elf64_Shdr* sh_table = elf64->s_hdr;
    Elf64_Ehdr* eh = elf64->hdr;
    int snmdx = eh->e_shstrndx;

    unsigned char* sh_str = (unsigned char*) rv_context->mem + sh_table[snmdx].sh_addr;
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