#include <rvcontext.h>


void rvContextInit(RVContext* rv_context, Elf64_t* elf64, FILE* err_str) {
    //Find the address of the text segment and put it into the pc.
    rv_context->rip_s7 = elf64->hdr->e_entry;
    rv_context->inst_ptr = elf64->sect + rv_context->rip_s7;
            //Set stack and frame pointer values to the same value.
    rv_context->rbp_fp = rv_context->rsp_sp;
}

void rvContextExecute(RVContext* rv_context, ZydisDecodedInstruction* instruction, Elf64_t* elf64, FILE* err_str) {
    rv_context->inst_ptr += instruction->length;
    rv_context->rip_s7 += instruction->length;
}

bool rvContextEndOfExecution(RVContext* rv_context) {
    return rv_context->gp == rv_context->rip_s7;
}