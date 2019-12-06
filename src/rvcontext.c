#include <rvcontext.h>

void copyRegOperandToTempInContext(RVContext* rv_context, ZydisRegister reg, size_t tmp_idx) {
    switch (reg) {
        default:
        case ZYDIS_REGISTER_NONE:
            rv_context->t[tmp_idx] = rv_context->x0;
            break;
        case ZYDIS_REGISTER_AL:
        case ZYDIS_REGISTER_AX:
        case ZYDIS_REGISTER_AH:
        case ZYDIS_REGISTER_EAX:
        case ZYDIS_REGISTER_RAX:
            rv_context->t[tmp_idx] = rv_context->rax_s1;
            break;
        case ZYDIS_REGISTER_BL:
        case ZYDIS_REGISTER_BX:
        case ZYDIS_REGISTER_BH:
        case ZYDIS_REGISTER_EBX:
        case ZYDIS_REGISTER_RBX:
            rv_context->t[tmp_idx] = (rv_context->rbx_s2);
            break;
        case ZYDIS_REGISTER_CL:
        case ZYDIS_REGISTER_CX:
        case ZYDIS_REGISTER_CH:
        case ZYDIS_REGISTER_ECX:
        case ZYDIS_REGISTER_RCX:
            rv_context->t[tmp_idx] = (rv_context->rcx_s3);
            break;
        case ZYDIS_REGISTER_DL:
        case ZYDIS_REGISTER_DX:
        case ZYDIS_REGISTER_DH:
        case ZYDIS_REGISTER_EDX:
        case ZYDIS_REGISTER_RDX:
            rv_context->t[tmp_idx] = (rv_context->rdx_s4);
            break;
        case ZYDIS_REGISTER_BPL:
        case ZYDIS_REGISTER_BP:
        case ZYDIS_REGISTER_EBP:
        case ZYDIS_REGISTER_RBP:
            rv_context->t[tmp_idx] = (rv_context->rbp_fp);
            break;
        case ZYDIS_REGISTER_SPL:
        case ZYDIS_REGISTER_SP:
        case ZYDIS_REGISTER_ESP:
        case ZYDIS_REGISTER_RSP:
            rv_context->t[tmp_idx] = (rv_context->rsp_sp);
            break;
        case ZYDIS_REGISTER_DIL:
        case ZYDIS_REGISTER_DI:
        case ZYDIS_REGISTER_EDI:
        case ZYDIS_REGISTER_RDI:
            rv_context->t[tmp_idx] = (rv_context->rdi_s5);
            break;
        case ZYDIS_REGISTER_SIL:
        case ZYDIS_REGISTER_SI:
        case ZYDIS_REGISTER_ESI:
        case ZYDIS_REGISTER_RSI:
            rv_context->t[tmp_idx] = (rv_context->rsi_s6);
            break;
        case ZYDIS_REGISTER_IP:
        case ZYDIS_REGISTER_EIP:
        case ZYDIS_REGISTER_RIP:
            rv_context->t[tmp_idx] = (rv_context->rip_s7);
            break;
        case ZYDIS_REGISTER_DS:
            rv_context->t[tmp_idx] = (ZyanU64) (rv_context->seg_s8.ds);
            break;
        case ZYDIS_REGISTER_CS:
            rv_context->t[tmp_idx] = (ZyanU64) (rv_context->seg_s8.cs);
            break;
        case ZYDIS_REGISTER_ES:
            rv_context->t[tmp_idx] = (ZyanU64) (rv_context->seg_s9.es);
            break;
        case ZYDIS_REGISTER_SS:
            rv_context->t[tmp_idx] = (ZyanU64) (rv_context->seg_s9.ss);
            break;
        case ZYDIS_REGISTER_FS:
            rv_context->t[tmp_idx] = (ZyanU64) (rv_context->seg_s9.fs);
            break;
        case ZYDIS_REGISTER_GS:
            rv_context->t[tmp_idx] = (ZyanU64) (rv_context->seg_s9.gs);
            break;
        case ZYDIS_REGISTER_R8B:
        case ZYDIS_REGISTER_R8W:
        case ZYDIS_REGISTER_R8D:
        case ZYDIS_REGISTER_R8:
            rv_context->t[tmp_idx] = (rv_context->r8_s11);
            break;
        case ZYDIS_REGISTER_R9B:
        case ZYDIS_REGISTER_R9W:
        case ZYDIS_REGISTER_R9D:
        case ZYDIS_REGISTER_R9:
            rv_context->t[tmp_idx] = (rv_context->r9_a0);
            break;
        case ZYDIS_REGISTER_R10B:
        case ZYDIS_REGISTER_R10W:
        case ZYDIS_REGISTER_R10D:
        case ZYDIS_REGISTER_R10:
            rv_context->t[tmp_idx] = (rv_context->r10_a1);
            break;
        case ZYDIS_REGISTER_R11B:
        case ZYDIS_REGISTER_R11W:
        case ZYDIS_REGISTER_R11D:
        case ZYDIS_REGISTER_R11:
            rv_context->t[tmp_idx] = (rv_context->r11_a2);
            break;
        case ZYDIS_REGISTER_R12B:
        case ZYDIS_REGISTER_R12W:
        case ZYDIS_REGISTER_R12D:
        case ZYDIS_REGISTER_R12:
            rv_context->t[tmp_idx] = (rv_context->r12_a3);
            break;
        case ZYDIS_REGISTER_R13B:
        case ZYDIS_REGISTER_R13W:
        case ZYDIS_REGISTER_R13D:
        case ZYDIS_REGISTER_R13:
            rv_context->t[tmp_idx] = (rv_context->r13_a4);
            break;
        case ZYDIS_REGISTER_R14B:
        case ZYDIS_REGISTER_R14W:
        case ZYDIS_REGISTER_R14D:
        case ZYDIS_REGISTER_R14:
            rv_context->t[tmp_idx] = (rv_context->r14_a5);
            break;
        case ZYDIS_REGISTER_R15B:
        case ZYDIS_REGISTER_R15W:
        case ZYDIS_REGISTER_R15D:
        case ZYDIS_REGISTER_R15:
            rv_context->t[tmp_idx] = (rv_context->r15_a6);
            break;
        case ZYDIS_REGISTER_FLAGS:
        case ZYDIS_REGISTER_EFLAGS:
        case ZYDIS_REGISTER_RFLAGS:
            rv_context->t[tmp_idx] = (ZyanU64) &(rv_context->r_flags_s10);
            break;
    }
}

void commitRegOperandFromTempInContext(RVContext* rv_context, ZydisRegister reg, size_t tmp_idx) {
    switch (reg) {
        default:
        case ZYDIS_REGISTER_NONE:
            break;
        case ZYDIS_REGISTER_AL:
        case ZYDIS_REGISTER_AX:
        case ZYDIS_REGISTER_AH:
        case ZYDIS_REGISTER_EAX:
        case ZYDIS_REGISTER_RAX:
            rv_context->rax_s1 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_BL:
        case ZYDIS_REGISTER_BX:
        case ZYDIS_REGISTER_BH:
        case ZYDIS_REGISTER_EBX:
        case ZYDIS_REGISTER_RBX:
            rv_context->rbx_s2 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_CL:
        case ZYDIS_REGISTER_CX:
        case ZYDIS_REGISTER_CH:
        case ZYDIS_REGISTER_ECX:
        case ZYDIS_REGISTER_RCX:
            rv_context->rcx_s3 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_DL:
        case ZYDIS_REGISTER_DX:
        case ZYDIS_REGISTER_DH:
        case ZYDIS_REGISTER_EDX:
        case ZYDIS_REGISTER_RDX:
            rv_context->rdx_s4 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_BPL:
        case ZYDIS_REGISTER_BP:
        case ZYDIS_REGISTER_EBP:
        case ZYDIS_REGISTER_RBP:
            rv_context->rbp_fp = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_SPL:
        case ZYDIS_REGISTER_SP:
        case ZYDIS_REGISTER_ESP:
        case ZYDIS_REGISTER_RSP:
            rv_context->rsp_sp = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_DIL:
        case ZYDIS_REGISTER_DI:
        case ZYDIS_REGISTER_EDI:
        case ZYDIS_REGISTER_RDI:
            rv_context->rdi_s5 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_SIL:
        case ZYDIS_REGISTER_SI:
        case ZYDIS_REGISTER_ESI:
        case ZYDIS_REGISTER_RSI:
            rv_context->rsi_s6 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_IP:
        case ZYDIS_REGISTER_EIP:
        case ZYDIS_REGISTER_RIP:
            rv_context->rip_s7 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_DS:
            rv_context->seg_s8.ds = (ZyanU16) rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_CS:
            rv_context->seg_s8.cs = (ZyanU16) rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_ES:
            rv_context->seg_s9.es = (ZyanU16) rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_SS:
            rv_context->seg_s9.ss = (ZyanU16) rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_FS:
            rv_context->seg_s9.fs = (ZyanU16) rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_GS:
            rv_context->seg_s9.gs = (ZyanU16) rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R8B:
        case ZYDIS_REGISTER_R8W:
        case ZYDIS_REGISTER_R8D:
        case ZYDIS_REGISTER_R8:
            rv_context->r8_s11 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R9B:
        case ZYDIS_REGISTER_R9W:
        case ZYDIS_REGISTER_R9D:
        case ZYDIS_REGISTER_R9:
            rv_context->r9_a0 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R10B:
        case ZYDIS_REGISTER_R10W:
        case ZYDIS_REGISTER_R10D:
        case ZYDIS_REGISTER_R10:
            rv_context->r10_a1 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R11B:
        case ZYDIS_REGISTER_R11W:
        case ZYDIS_REGISTER_R11D:
        case ZYDIS_REGISTER_R11:
            rv_context->r11_a2 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R12B:
        case ZYDIS_REGISTER_R12W:
        case ZYDIS_REGISTER_R12D:
        case ZYDIS_REGISTER_R12:
            rv_context->r12_a3 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R13B:
        case ZYDIS_REGISTER_R13W:
        case ZYDIS_REGISTER_R13D:
        case ZYDIS_REGISTER_R13:
            rv_context->r13_a4 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R14B:
        case ZYDIS_REGISTER_R14W:
        case ZYDIS_REGISTER_R14D:
        case ZYDIS_REGISTER_R14:
            rv_context->r14_a5 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_R15B:
        case ZYDIS_REGISTER_R15W:
        case ZYDIS_REGISTER_R15D:
        case ZYDIS_REGISTER_R15:
            rv_context->r15_a6 = rv_context->t[tmp_idx];
            break;
        case ZYDIS_REGISTER_FLAGS:
        case ZYDIS_REGISTER_EFLAGS:
        case ZYDIS_REGISTER_RFLAGS:
            rv_context->r_flags_s10 = *((Flag*) rv_context->t[tmp_idx]);
    }
}

void copyMemOperandToTempInContext(RVContext* rv_context, ZydisDecodedOperand operand, size_t tmp_idx, FILE* err_str) {
    //tmp_idx = seg_reg.
    copyRegOperandToTempInContext(rv_context, operand.mem.segment, tmp_idx);
    //$7 = base_reg.
    copyRegOperandToTempInContext(rv_context, operand.mem.base, 6);
    //$8 = index_reg
    copyRegOperandToTempInContext(rv_context, operand.mem.index, 7);
    switch (operand.mem.type) {
        case ZYDIS_MEMOP_TYPE_INVALID:
            fprintf(err_str, "Encountered an invalid memory operand.");
            break;
        case ZYDIS_MEMOP_TYPE_MEM:
            break;
        case ZYDIS_MEMOP_TYPE_AGEN:
            //Indirect address generation with register values.
            rv_context->t[tmp_idx] = rv_context->t[6] + rv_context->t[tmp_idx] + rv_context->t[7] * operand.mem.scale +
                    operand.mem.disp.value;
        case ZYDIS_MEMOP_TYPE_MIB:
            break;
    }
}

void copyPtrOperandToTempInContext(RVContext* rv_context, ZydisDecodedOperand operand, size_t tmp_idx, FILE* err_str) {

}

void copyImmOperandToTempInContext(RVContext* rv_context, ZydisDecodedOperand operand, size_t tmp_idx) {
    if (operand.imm.is_signed) {
        rv_context->t[tmp_idx] = (ZyanU64) operand.imm.value.s;
    }
    else {
        rv_context->t[tmp_idx] = (ZyanU64) operand.imm.value.u;
    }
}

void copyOperandToTempInContext(RVContext* rv_context, ZydisDecodedOperand operand, size_t tmp_idx, FILE* err_str) {
    switch(operand.type) {
        default:
        case ZYDIS_ELEMENT_TYPE_INVALID:
            fprintf(err_str, "Warning: an invalid operand was parsed!\n");
            rv_context->t[tmp_idx] = (ZyanU64) ZYAN_NULL;
            break;
        case ZYDIS_OPERAND_TYPE_REGISTER:
            copyRegOperandToTempInContext(rv_context, operand.reg.value, tmp_idx);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            copyMemOperandToTempInContext(rv_context, operand, tmp_idx, err_str);
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            copyPtrOperandToTempInContext(rv_context, operand, tmp_idx, err_str);
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            copyImmOperandToTempInContext(rv_context, operand, tmp_idx);
            break;
    }
}

void commitOperandFromTempInContext(RVContext* rvContext, ZydisDecodedOperand operand, size_t tmp_idx, FILE* err_str) {
    switch(operand.type) {
        default:
        case ZYDIS_ELEMENT_TYPE_INVALID:
            fprintf(err_str, "Warning: an invalid destination operand was parsed!\n");
            break;
        case ZYDIS_OPERAND_TYPE_REGISTER:
            commitRegOperandFromTempInContext(rvContext, operand.reg.value, tmp_idx);
            break;
        case ZYDIS_OPERAND_TYPE_MEMORY:
            fprintf(err_str, "Not implemented!");
            break;
        case ZYDIS_OPERAND_TYPE_POINTER:
            fprintf(err_str, "Not implemented!");
            break;
        case ZYDIS_OPERAND_TYPE_IMMEDIATE:
            fprintf(err_str, "Warning: an immediate operand was set as destination!\n");
            break;
    }
}

void preserveMSBs(RVContext* rv_context, size_t addr_size_idx, size_t src_idx, size_t dst_idx) {
    rv_context->t[dst_idx] = rv_context->t[src_idx] >> rv_context->t[addr_size_idx];
    rv_context->t[dst_idx] = rv_context->t[dst_idx] << rv_context->t[addr_size_idx];
}

void preserveLSBs(RVContext* rv_context, size_t addr_size_idx, size_t src_idx, size_t dst_idx) {
    rv_context->t[addr_size_idx] = 64 - rv_context->t[addr_size_idx];
    rv_context->t[dst_idx] = rv_context->t[src_idx] << rv_context->t[addr_size_idx];
    rv_context->t[dst_idx] = rv_context->t[dst_idx] >> rv_context->t[addr_size_idx];
    //Just to restore state. It can be removed if very necessary.
    rv_context->t[addr_size_idx] = 64 - rv_context->t[addr_size_idx];
}

void executeXOR(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    //op_dst = $0
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //op_src = $1
    copyOperandToTempInContext(rv_context, instruction->operands[1], 1, err_str);
    //msb_dst = $3
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 3);
    //result = $1
    rv_context->t[1] = rv_context->t[0] ^ rv_context->t[1];
    //lsb_result = $1
    preserveLSBs(rv_context, 2, 1, 1);
    //combine the results in $0
    rv_context->t[0] = (rv_context->t[1]) | (rv_context->t[3]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //Flags
    rv_context->r_flags_s10.of = rv_context->r_flags_s10.cf = 0;
    rv_context->r_flags_s10.zf = (rv_context->t[0] == 0);
    rv_context->r_flags_s10.sf = (rv_context->t[0] < 0);
    //TODO: Add Parity.
}

void executeMOV(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    //op_dst = $0
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //op_src = $1
    copyOperandToTempInContext(rv_context, instruction->operands[1], 1, err_str);
    //msb_dst = $0
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 0);
    //lsb_src - $1
    preserveLSBs(rv_context, 2, 1, 1);
    //Combine the results in $0
    rv_context->t[0] = (rv_context->t[0]) | (rv_context->t[1]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executePOP(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //Read the memory associated with the stack pointer and put it in $1
    rv_context->t[1] = (ZyanU64) (rv_context->mem + rv_context->rsp_sp);
    //$1 will have the contents of the address after this switch statement.
    switch (instruction->operand_width) {
        case 16:
            rv_context->t[1] = *((ZyanU16*) rv_context->t[1]);
            rv_context->rsp_sp += 2;
            break;
        case 32:
            rv_context->t[1] = *((ZyanU32*) rv_context->t[1]);
            rv_context->rsp_sp += 4;
            break;
        case 64:
            rv_context->t[1] = *((ZyanU64*) rv_context->t[1]);
            rv_context->rsp_sp += 8;
            break;
    }
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 0);
    preserveLSBs(rv_context, 2, 1, 1);
    rv_context->t[0] = (rv_context->t[1]) | (rv_context->t[0]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeAND(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    copyOperandToTempInContext(rv_context, instruction->operands[1], 1, err_str);
    //msb_dst = $3
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 3);
    //result = $1
    rv_context->t[1] = rv_context->t[0] & rv_context->t[1];
    //lsb_result = $1
    preserveLSBs(rv_context, 2, 1, 1);
    //combine the results in $0
    rv_context->t[0] = (rv_context->t[1]) | (rv_context->t[3]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //Flags
    rv_context->r_flags_s10.of = rv_context->r_flags_s10.cf = 0;
    rv_context->r_flags_s10.zf = (rv_context->t[4] == 0);
    rv_context->r_flags_s10.sf = (rv_context->t[4] < 0);
}

void executePUSH(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //LSB_src = $0
    rv_context->t[2] = instruction->operand_width;
    preserveLSBs(rv_context, 2, 0, 0);
    //Read the memory associated with the stack pointer.
    rv_context->t[2] = rv_context->t[2] >> 3;
    rv_context->rsp_sp -= rv_context->t[2];
    rv_context->t[1] = (ZyanU64) rv_context->mem + rv_context->rsp_sp;
    switch (instruction->operand_width) {
        case 16:
            *((ZyanU16*) rv_context->t[1]) = rv_context->t[0];
            break;
        case 32:
            *((ZyanU32*) rv_context->t[1]) = rv_context->t[0];
            break;
        case 64:
            *((ZyanU64*) rv_context->t[1]) = rv_context->t[0];
            break;
    }
}

void executeLEA(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    //dst = $0
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //src = $1
    copyOperandToTempInContext(rv_context, instruction->operands[1], 1, err_str);
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 0);
    preserveLSBs(rv_context, 2, 1, 1);
    rv_context->t[0] = (rv_context->t[0]) | (rv_context->t[1]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeSUB(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    //dst = $0
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //src = $1
    copyOperandToTempInContext(rv_context, instruction->operands[1], 1, err_str);
    //MSB_dst = $3
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 3);
    //result = $0
    rv_context->t[0] = rv_context->t[0] - rv_context->t[1];
    //LSB_result = $0
    preserveLSBs(rv_context, 2, 0, 0);
    rv_context->t[0] = (rv_context->t[0]) | (rv_context->t[3]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //TODO: Flags;
    rv_context->r_flags_s10.of = rv_context->r_flags_s10.cf = 0;
    rv_context->r_flags_s10.zf = (rv_context->t[4] == 0);
    rv_context->r_flags_s10.sf = (rv_context->t[4] < 0);
}

void executeSAR(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeCALL(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeTEST(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeJZ(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeADD(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    //dst = $0
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //src = $1
    copyOperandToTempInContext(rv_context, instruction->operands[1], 1, err_str);
    //MSB_dst = $3
    rv_context->t[2] = instruction->operand_width;
    preserveMSBs(rv_context, 2, 0, 3);
    //result = $0
    rv_context->t[0] = rv_context->t[0] + rv_context->t[1];
    //LSB_result = $0
    preserveLSBs(rv_context, 2, 0, 0);
    rv_context->t[0] = (rv_context->t[0]) | (rv_context->t[3]);
    commitOperandFromTempInContext(rv_context, instruction->operands[0], 0, err_str);
    //TODO: Flags;
    rv_context->r_flags_s10.of = rv_context->r_flags_s10.cf = 0;
    rv_context->r_flags_s10.zf = (rv_context->t[4] == 0);
    rv_context->r_flags_s10.sf = (rv_context->t[4] < 0);
}

void executeRET(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeCMP(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeHLT(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {

}

void executeNOP(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeJMP(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
    copyOperandToTempInContext(rv_context, instruction->operands[0], 0, err_str);
}

void executeSHR(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
}

void executeJNZ(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
}

void executeLEAVE(RVContext* rv_context, ZydisDecodedInstruction* instruction, FILE* err_str) {
}


void rvContextInitMemoryVars(RVContext *rv_context, Elf64_t* elf64, ZyanUSize stack_mem) {
    Elf64_Ehdr* elf_header = elf64->hdr;
    Elf64_Shdr* s_hdr_table = elf64->s_hdr;
    ZyanUSize mem_size = 0;
    //Find the Size of the address space specified by the elf file.
    for (int i = elf_header->e_shnum - 1; i > -1; i--) {
        if (s_hdr_table[i].sh_addr > 0) {
            mem_size = s_hdr_table[i].sh_addr + s_hdr_table[i].sh_size;
            break;
        }
    }
    //Allocate the memory and read in the memory image from the elf file.
    rv_context->mem = malloc(mem_size + stack_mem);
    rv_context->rbp_fp = rv_context->rsp_sp = (ZyanU64) mem_size;
    for (int i = 0; i < elf_header->e_shnum; i++) {
        if (s_hdr_table[i].sh_flags != 0 && s_hdr_table[i].sh_flags != 0x30) {
            lseek(elf64->fd, (off_t) s_hdr_table[i].sh_offset, SEEK_SET);
            read(elf64->fd, (void *) (rv_context->mem + s_hdr_table[i].sh_addr), s_hdr_table[i].sh_size);
        }
    }
    //Find the global pointer, where our program ends.
    unsigned char* sh_str = (unsigned char*) elf64->s_names;
    for (int i = 0; i < elf_header->e_shnum; i++) {
        if(!strcmp(sh_str + s_hdr_table[i].sh_name, ".fini")) {
            rv_context->gp = s_hdr_table[i].sh_addr + s_hdr_table[i].sh_size;
            break;
        }
    }

}


void rvContextInit(RVContext* rv_context, Elf64_t* elf64, FILE* err_str) {
    //Find the address of the text segment and put it into the pc.
    rv_context->x0 = 0;
    rv_context->rip_s7 = elf64->hdr->e_entry;
    //Initialize memory and memory related registers.
    rvContextInitMemoryVars(rv_context, elf64, 1024);
}


void rvContextExecute(RVContext* rv_context, ZydisDecodedInstruction* instruction, Elf64_t* elf64, FILE* err_str) {
    //A giant case switch statement to call the function associated with each instruction.
    switch (instruction->mnemonic) {
        default:
        case ZYDIS_MNEMONIC_INVALID:
            break;
        case ZYDIS_MNEMONIC_ADD:
            executeADD(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_AND:
            executeAND(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_CALL:
            executeCALL(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_CMP:
            executeCMP(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_HLT:
            executeHLT(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_JMP:
            executeJMP(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_JNZ:
            executeJNZ(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_JZ:
            executeJZ(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_LEA:
            executeLEA(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_LEAVE:
            executeLEAVE(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_MOV:
            executeMOV(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_NOP:
            executeNOP(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_POP:
            executePOP(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_PUSH:
            executePUSH(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_RET:
            executeRET(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_SAR:
            executeSAR(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_SHR:
            executeSHR(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_SUB:
            executeSUB(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_TEST:
            executeTEST(rv_context, instruction, err_str);
            break;
        case ZYDIS_MNEMONIC_XOR:
            executeXOR(rv_context, instruction, err_str);
            break;
    }

    rv_context->rip_s7 += instruction->length;
}


bool rvContextEndOfExecution(RVContext* rv_context) {
    return rv_context->gp == rv_context->rip_s7;
}

void rvContextDestroy(RVContext* rv_context) {
    free(rv_context->mem);
}

