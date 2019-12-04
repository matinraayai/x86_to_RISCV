#include <encoder.h>


void rvContextInit(RVContext* rv_context, Elf64_t* elf64, FILE* err_str) {
    //Find the address of the text segment and put it into the pc.
    uint32_t txt_sec_idx = elfTextSectionIndex(elf64, err_str);
    rv_context->rip_s7 = elf64->s_hdr[txt_sec_idx].sh_addr;
    //Set stack and frame pointer values to the same value.
    rv_context->rbp_fp = rv_context->rsp_sp;
    rv_context->inst_ptr = elf64->sect[txt_sec_idx][0];
}

void rvContextExecute(RVContext* rv_context, Elf64_t* elf64, FILE* err_str) {
    
}