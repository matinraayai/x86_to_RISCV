#ifndef X86_TO_RISCV_RVCONTEXT_H
#define X86_TO_RISCV_RVCONTEXT_H
#include <elfparse.h>
#include <Zydis/DecoderTypes.h>

typedef struct context_ {
    //TODO: Move the memory segment here instead of the elf file.
    ZyanU8* mem; // All Sections combined.
    //General Purpose Registers:
    ZyanU64 rax_s1;
    ZyanU64 rbx_s2;
    ZyanU64 rcx_s3;
    ZyanU64 rdx_s4;
    //Index and Pointer Registers:
    ZyanU64 rbp_fp; //Frame pointer, base pointer for stack.
    ZyanU64 rsp_sp; //Stack pointer in both x86 and RISC-V.
    ZyanU64 gp; //Global pointer for RISC-V. Great for detecting end of execution.
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
    ZyanU8* inst_ptr; //A pointer to the current instruction in the mother process. Might be removed as it's not really
    //needed.
} RVContext;

void rvContextInit(RVContext* rv_context, Elf64_t* elf64, FILE* err_str);

void rvContextInitMemoryVars(RVContext *rv_context, Elf64_t* elf64, ZyanUSize stack_mem);

void rvContextExecute(RVContext* rv_context, ZydisDecodedInstruction* instruction, Elf64_t* elf64, FILE* err_str);

bool rvContextEndOfExecution(RVContext* rv_context);


//Had to move these here due to the need to access memory.
//TODO: move this back to elf parse.
void printSectionHeaders(Elf64_t* elf64, RVContext* rv_context);

void printProgramHeaders(Elf64_t* elf64);
#endif //X86_TO_RISCV_RVCONTEXT_H
