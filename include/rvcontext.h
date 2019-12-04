#ifndef X86_TO_RISCV_ENCODER_H
#define X86_TO_RISCV_ENCODER_H
#include <elfparse.h>

typedef struct context_ {
    //General Purpose Registers:
    ZyanU64 rax_s1;
    ZyanU64 rbx_s2;
    ZyanU64 rcx_s3;
    ZyanU64 rdx_s4;
    //Index and Pointer Registers:
    ZyanU64 rbp_fp; //Frame pointer, base pointer for stack.
    ZyanU64 rsp_sp; //Stack pointer in both x86 and RISC-V.
    ZyanU64 rdi_s5;
    ZyanU64 rsi_s6;
    ZyanU64 rip_s7; //Instruction Pointer, have no choice but to map it to a GPR in RISC-V.
    struct {
        ZyanU32 ds; //The legacy data segment register.
        ZyanU32 cs; //The legacy Code segment register. Needed for Nop operation.
    } seg_s8;
    struct {
        ZyanU16 ss; //Stack segment register. Might not be needed by modern OS.
        ZyanU16 es; //Extra segment register.
        ZyanU16 fs; //Extra segment register.
        ZyanU16 gs; //Extra segment register.
    } seg_s9;
    ZyanU64 r_flags_s10;
    ZyanU64 r8_s11;
    ZyanU64 r9_a0; //No need for function call registers, x86 can handle calling conventions itself.
    ZyanU64 r10_a1;
    ZyanU64 r11_a2;
    ZyanU64 r12_a3;
    ZyanU64 r13_a4;
    ZyanU64 r14_a5;
    ZyanU64 r15_a6;
    ZyanUSize inst_ptr; //A pointer to the current instruction in the mother process.
} RVContext;

void rvContextInit(RVContext* rv_context, Elf64_t* elf64, FILE* err_str);

#endif //X86_TO_RISCV_ENCODER_H
