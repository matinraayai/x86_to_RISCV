#include <encoder.h>


void rvContextInit(RVContext* rvContext, Elf64_t* elf64, FILE* err_str) {
    //Find the address of the text segment and put it into the pc.
    uint32_t txt_sec_idx = elfTextSectionIndex(elf64, err_str);
    rvContext->rip_s7 = elf64->s_hdr[txt_sec_idx].sh_addr;
    //
}