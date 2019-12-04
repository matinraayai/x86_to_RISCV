#include <rvcontext.h>

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
    rv_context->rip_s7 = elf64->hdr->e_entry;
    //Initialize memory and memory related registers.
    rvContextInitMemoryVars(rv_context, elf64, 1024);
}


void rvContextExecute(RVContext* rv_context, ZydisDecodedInstruction* instruction, Elf64_t* elf64, FILE* err_str) {
    //A giant case switch statement to call the function associated with each instruction.
    switch (instruction->mnemonic) {
        case ZYDIS_MNEMONIC_INVALID:
            break;
        case ZYDIS_MNEMONIC_AAA:
            break;
        case ZYDIS_MNEMONIC_AAD:
            break;
        case ZYDIS_MNEMONIC_AAM:
            break;
        case ZYDIS_MNEMONIC_AAS:
            break;
        case ZYDIS_MNEMONIC_ADC:
            break;
        case ZYDIS_MNEMONIC_ADCX:
            break;
        case ZYDIS_MNEMONIC_ADD:
            break;
        case ZYDIS_MNEMONIC_ADDPD:
            break;
        case ZYDIS_MNEMONIC_ADDPS:
            break;
        case ZYDIS_MNEMONIC_ADDSD:
            break;
        case ZYDIS_MNEMONIC_ADDSS:
            break;
        case ZYDIS_MNEMONIC_ADDSUBPD:
            break;
        case ZYDIS_MNEMONIC_ADDSUBPS:
            break;
        case ZYDIS_MNEMONIC_ADOX:
            break;
        case ZYDIS_MNEMONIC_AESDEC:
            break;
        case ZYDIS_MNEMONIC_AESDECLAST:
            break;
        case ZYDIS_MNEMONIC_AESENC:
            break;
        case ZYDIS_MNEMONIC_AESENCLAST:
            break;
        case ZYDIS_MNEMONIC_AESIMC:
            break;
        case ZYDIS_MNEMONIC_AESKEYGENASSIST:
            break;
        case ZYDIS_MNEMONIC_AND:
            break;
        case ZYDIS_MNEMONIC_ANDN:
            break;
        case ZYDIS_MNEMONIC_ANDNPD:
            break;
        case ZYDIS_MNEMONIC_ANDNPS:
            break;
        case ZYDIS_MNEMONIC_ANDPD:
            break;
        case ZYDIS_MNEMONIC_ANDPS:
            break;
        case ZYDIS_MNEMONIC_ARPL:
            break;
        case ZYDIS_MNEMONIC_BEXTR:
            break;
        case ZYDIS_MNEMONIC_BLCFILL:
            break;
        case ZYDIS_MNEMONIC_BLCI:
            break;
        case ZYDIS_MNEMONIC_BLCIC:
            break;
        case ZYDIS_MNEMONIC_BLCMSK:
            break;
        case ZYDIS_MNEMONIC_BLCS:
            break;
        case ZYDIS_MNEMONIC_BLENDPD:
            break;
        case ZYDIS_MNEMONIC_BLENDPS:
            break;
        case ZYDIS_MNEMONIC_BLENDVPD:
            break;
        case ZYDIS_MNEMONIC_BLENDVPS:
            break;
        case ZYDIS_MNEMONIC_BLSFILL:
            break;
        case ZYDIS_MNEMONIC_BLSI:
            break;
        case ZYDIS_MNEMONIC_BLSIC:
            break;
        case ZYDIS_MNEMONIC_BLSMSK:
            break;
        case ZYDIS_MNEMONIC_BLSR:
            break;
        case ZYDIS_MNEMONIC_BNDCL:
            break;
        case ZYDIS_MNEMONIC_BNDCN:
            break;
        case ZYDIS_MNEMONIC_BNDCU:
            break;
        case ZYDIS_MNEMONIC_BNDLDX:
            break;
        case ZYDIS_MNEMONIC_BNDMK:
            break;
        case ZYDIS_MNEMONIC_BNDMOV:
            break;
        case ZYDIS_MNEMONIC_BNDSTX:
            break;
        case ZYDIS_MNEMONIC_BOUND:
            break;
        case ZYDIS_MNEMONIC_BSF:
            break;
        case ZYDIS_MNEMONIC_BSR:
            break;
        case ZYDIS_MNEMONIC_BSWAP:
            break;
        case ZYDIS_MNEMONIC_BT:
            break;
        case ZYDIS_MNEMONIC_BTC:
            break;
        case ZYDIS_MNEMONIC_BTR:
            break;
        case ZYDIS_MNEMONIC_BTS:
            break;
        case ZYDIS_MNEMONIC_BZHI:
            break;
        case ZYDIS_MNEMONIC_CALL:
            break;
        case ZYDIS_MNEMONIC_CBW:
            break;
        case ZYDIS_MNEMONIC_CDQ:
            break;
        case ZYDIS_MNEMONIC_CDQE:
            break;
        case ZYDIS_MNEMONIC_CLAC:
            break;
        case ZYDIS_MNEMONIC_CLC:
            break;
        case ZYDIS_MNEMONIC_CLD:
            break;
        case ZYDIS_MNEMONIC_CLDEMOTE:
            break;
        case ZYDIS_MNEMONIC_CLEVICT0:
            break;
        case ZYDIS_MNEMONIC_CLEVICT1:
            break;
        case ZYDIS_MNEMONIC_CLFLUSH:
            break;
        case ZYDIS_MNEMONIC_CLFLUSHOPT:
            break;
        case ZYDIS_MNEMONIC_CLGI:
            break;
        case ZYDIS_MNEMONIC_CLI:
            break;
        case ZYDIS_MNEMONIC_CLRSSBSY:
            break;
        case ZYDIS_MNEMONIC_CLTS:
            break;
        case ZYDIS_MNEMONIC_CLWB:
            break;
        case ZYDIS_MNEMONIC_CLZERO:
            break;
        case ZYDIS_MNEMONIC_CMC:
            break;
        case ZYDIS_MNEMONIC_CMOVB:
            break;
        case ZYDIS_MNEMONIC_CMOVBE:
            break;
        case ZYDIS_MNEMONIC_CMOVL:
            break;
        case ZYDIS_MNEMONIC_CMOVLE:
            break;
        case ZYDIS_MNEMONIC_CMOVNB:
            break;
        case ZYDIS_MNEMONIC_CMOVNBE:
            break;
        case ZYDIS_MNEMONIC_CMOVNL:
            break;
        case ZYDIS_MNEMONIC_CMOVNLE:
            break;
        case ZYDIS_MNEMONIC_CMOVNO:
            break;
        case ZYDIS_MNEMONIC_CMOVNP:
            break;
        case ZYDIS_MNEMONIC_CMOVNS:
            break;
        case ZYDIS_MNEMONIC_CMOVNZ:
            break;
        case ZYDIS_MNEMONIC_CMOVO:
            break;
        case ZYDIS_MNEMONIC_CMOVP:
            break;
        case ZYDIS_MNEMONIC_CMOVS:
            break;
        case ZYDIS_MNEMONIC_CMOVZ:
            break;
        case ZYDIS_MNEMONIC_CMP:
            break;
        case ZYDIS_MNEMONIC_CMPPD:
            break;
        case ZYDIS_MNEMONIC_CMPPS:
            break;
        case ZYDIS_MNEMONIC_CMPSB:
            break;
        case ZYDIS_MNEMONIC_CMPSD:
            break;
        case ZYDIS_MNEMONIC_CMPSQ:
            break;
        case ZYDIS_MNEMONIC_CMPSS:
            break;
        case ZYDIS_MNEMONIC_CMPSW:
            break;
        case ZYDIS_MNEMONIC_CMPXCHG:
            break;
        case ZYDIS_MNEMONIC_CMPXCHG16B:
            break;
        case ZYDIS_MNEMONIC_CMPXCHG8B:
            break;
        case ZYDIS_MNEMONIC_COMISD:
            break;
        case ZYDIS_MNEMONIC_COMISS:
            break;
        case ZYDIS_MNEMONIC_CPUID:
            break;
        case ZYDIS_MNEMONIC_CQO:
            break;
        case ZYDIS_MNEMONIC_CRC32:
            break;
        case ZYDIS_MNEMONIC_CVTDQ2PD:
            break;
        case ZYDIS_MNEMONIC_CVTDQ2PS:
            break;
        case ZYDIS_MNEMONIC_CVTPD2DQ:
            break;
        case ZYDIS_MNEMONIC_CVTPD2PI:
            break;
        case ZYDIS_MNEMONIC_CVTPD2PS:
            break;
        case ZYDIS_MNEMONIC_CVTPI2PD:
            break;
        case ZYDIS_MNEMONIC_CVTPI2PS:
            break;
        case ZYDIS_MNEMONIC_CVTPS2DQ:
            break;
        case ZYDIS_MNEMONIC_CVTPS2PD:
            break;
        case ZYDIS_MNEMONIC_CVTPS2PI:
            break;
        case ZYDIS_MNEMONIC_CVTSD2SI:
            break;
        case ZYDIS_MNEMONIC_CVTSD2SS:
            break;
        case ZYDIS_MNEMONIC_CVTSI2SD:
            break;
        case ZYDIS_MNEMONIC_CVTSI2SS:
            break;
        case ZYDIS_MNEMONIC_CVTSS2SD:
            break;
        case ZYDIS_MNEMONIC_CVTSS2SI:
            break;
        case ZYDIS_MNEMONIC_CVTTPD2DQ:
            break;
        case ZYDIS_MNEMONIC_CVTTPD2PI:
            break;
        case ZYDIS_MNEMONIC_CVTTPS2DQ:
            break;
        case ZYDIS_MNEMONIC_CVTTPS2PI:
            break;
        case ZYDIS_MNEMONIC_CVTTSD2SI:
            break;
        case ZYDIS_MNEMONIC_CVTTSS2SI:
            break;
        case ZYDIS_MNEMONIC_CWD:
            break;
        case ZYDIS_MNEMONIC_CWDE:
            break;
        case ZYDIS_MNEMONIC_DAA:
            break;
        case ZYDIS_MNEMONIC_DAS:
            break;
        case ZYDIS_MNEMONIC_DEC:
            break;
        case ZYDIS_MNEMONIC_DELAY:
            break;
        case ZYDIS_MNEMONIC_DIV:
            break;
        case ZYDIS_MNEMONIC_DIVPD:
            break;
        case ZYDIS_MNEMONIC_DIVPS:
            break;
        case ZYDIS_MNEMONIC_DIVSD:
            break;
        case ZYDIS_MNEMONIC_DIVSS:
            break;
        case ZYDIS_MNEMONIC_DPPD:
            break;
        case ZYDIS_MNEMONIC_DPPS:
            break;
        case ZYDIS_MNEMONIC_EMMS:
            break;
        case ZYDIS_MNEMONIC_ENCLS:
            break;
        case ZYDIS_MNEMONIC_ENCLU:
            break;
        case ZYDIS_MNEMONIC_ENCLV:
            break;
        case ZYDIS_MNEMONIC_ENDBR32:
            break;
        case ZYDIS_MNEMONIC_ENDBR64:
            break;
        case ZYDIS_MNEMONIC_ENQCMD:
            break;
        case ZYDIS_MNEMONIC_ENQCMDS:
            break;
        case ZYDIS_MNEMONIC_ENTER:
            break;
        case ZYDIS_MNEMONIC_EXTRACTPS:
            break;
        case ZYDIS_MNEMONIC_EXTRQ:
            break;
        case ZYDIS_MNEMONIC_F2XM1:
            break;
        case ZYDIS_MNEMONIC_FABS:
            break;
        case ZYDIS_MNEMONIC_FADD:
            break;
        case ZYDIS_MNEMONIC_FADDP:
            break;
        case ZYDIS_MNEMONIC_FBLD:
            break;
        case ZYDIS_MNEMONIC_FBSTP:
            break;
        case ZYDIS_MNEMONIC_FCHS:
            break;
        case ZYDIS_MNEMONIC_FCMOVB:
            break;
        case ZYDIS_MNEMONIC_FCMOVBE:
            break;
        case ZYDIS_MNEMONIC_FCMOVE:
            break;
        case ZYDIS_MNEMONIC_FCMOVNB:
            break;
        case ZYDIS_MNEMONIC_FCMOVNBE:
            break;
        case ZYDIS_MNEMONIC_FCMOVNE:
            break;
        case ZYDIS_MNEMONIC_FCMOVNU:
            break;
        case ZYDIS_MNEMONIC_FCMOVU:
            break;
        case ZYDIS_MNEMONIC_FCOM:
            break;
        case ZYDIS_MNEMONIC_FCOMI:
            break;
        case ZYDIS_MNEMONIC_FCOMIP:
            break;
        case ZYDIS_MNEMONIC_FCOMP:
            break;
        case ZYDIS_MNEMONIC_FCOMPP:
            break;
        case ZYDIS_MNEMONIC_FCOS:
            break;
        case ZYDIS_MNEMONIC_FDECSTP:
            break;
        case ZYDIS_MNEMONIC_FDISI8087_NOP:
            break;
        case ZYDIS_MNEMONIC_FDIV:
            break;
        case ZYDIS_MNEMONIC_FDIVP:
            break;
        case ZYDIS_MNEMONIC_FDIVR:
            break;
        case ZYDIS_MNEMONIC_FDIVRP:
            break;
        case ZYDIS_MNEMONIC_FEMMS:
            break;
        case ZYDIS_MNEMONIC_FENI8087_NOP:
            break;
        case ZYDIS_MNEMONIC_FFREE:
            break;
        case ZYDIS_MNEMONIC_FFREEP:
            break;
        case ZYDIS_MNEMONIC_FIADD:
            break;
        case ZYDIS_MNEMONIC_FICOM:
            break;
        case ZYDIS_MNEMONIC_FICOMP:
            break;
        case ZYDIS_MNEMONIC_FIDIV:
            break;
        case ZYDIS_MNEMONIC_FIDIVR:
            break;
        case ZYDIS_MNEMONIC_FILD:
            break;
        case ZYDIS_MNEMONIC_FIMUL:
            break;
        case ZYDIS_MNEMONIC_FINCSTP:
            break;
        case ZYDIS_MNEMONIC_FIST:
            break;
        case ZYDIS_MNEMONIC_FISTP:
            break;
        case ZYDIS_MNEMONIC_FISTTP:
            break;
        case ZYDIS_MNEMONIC_FISUB:
            break;
        case ZYDIS_MNEMONIC_FISUBR:
            break;
        case ZYDIS_MNEMONIC_FLD:
            break;
        case ZYDIS_MNEMONIC_FLD1:
            break;
        case ZYDIS_MNEMONIC_FLDCW:
            break;
        case ZYDIS_MNEMONIC_FLDENV:
            break;
        case ZYDIS_MNEMONIC_FLDL2E:
            break;
        case ZYDIS_MNEMONIC_FLDL2T:
            break;
        case ZYDIS_MNEMONIC_FLDLG2:
            break;
        case ZYDIS_MNEMONIC_FLDLN2:
            break;
        case ZYDIS_MNEMONIC_FLDPI:
            break;
        case ZYDIS_MNEMONIC_FLDZ:
            break;
        case ZYDIS_MNEMONIC_FMUL:
            break;
        case ZYDIS_MNEMONIC_FMULP:
            break;
        case ZYDIS_MNEMONIC_FNCLEX:
            break;
        case ZYDIS_MNEMONIC_FNINIT:
            break;
        case ZYDIS_MNEMONIC_FNOP:
            break;
        case ZYDIS_MNEMONIC_FNSAVE:
            break;
        case ZYDIS_MNEMONIC_FNSTCW:
            break;
        case ZYDIS_MNEMONIC_FNSTENV:
            break;
        case ZYDIS_MNEMONIC_FNSTSW:
            break;
        case ZYDIS_MNEMONIC_FPATAN:
            break;
        case ZYDIS_MNEMONIC_FPREM:
            break;
        case ZYDIS_MNEMONIC_FPREM1:
            break;
        case ZYDIS_MNEMONIC_FPTAN:
            break;
        case ZYDIS_MNEMONIC_FRNDINT:
            break;
        case ZYDIS_MNEMONIC_FRSTOR:
            break;
        case ZYDIS_MNEMONIC_FSCALE:
            break;
        case ZYDIS_MNEMONIC_FSETPM287_NOP:
            break;
        case ZYDIS_MNEMONIC_FSIN:
            break;
        case ZYDIS_MNEMONIC_FSINCOS:
            break;
        case ZYDIS_MNEMONIC_FSQRT:
            break;
        case ZYDIS_MNEMONIC_FST:
            break;
        case ZYDIS_MNEMONIC_FSTP:
            break;
        case ZYDIS_MNEMONIC_FSTPNCE:
            break;
        case ZYDIS_MNEMONIC_FSUB:
            break;
        case ZYDIS_MNEMONIC_FSUBP:
            break;
        case ZYDIS_MNEMONIC_FSUBR:
            break;
        case ZYDIS_MNEMONIC_FSUBRP:
            break;
        case ZYDIS_MNEMONIC_FTST:
            break;
        case ZYDIS_MNEMONIC_FUCOM:
            break;
        case ZYDIS_MNEMONIC_FUCOMI:
            break;
        case ZYDIS_MNEMONIC_FUCOMIP:
            break;
        case ZYDIS_MNEMONIC_FUCOMP:
            break;
        case ZYDIS_MNEMONIC_FUCOMPP:
            break;
        case ZYDIS_MNEMONIC_FWAIT:
            break;
        case ZYDIS_MNEMONIC_FXAM:
            break;
        case ZYDIS_MNEMONIC_FXCH:
            break;
        case ZYDIS_MNEMONIC_FXRSTOR:
            break;
        case ZYDIS_MNEMONIC_FXRSTOR64:
            break;
        case ZYDIS_MNEMONIC_FXSAVE:
            break;
        case ZYDIS_MNEMONIC_FXSAVE64:
            break;
        case ZYDIS_MNEMONIC_FXTRACT:
            break;
        case ZYDIS_MNEMONIC_FYL2X:
            break;
        case ZYDIS_MNEMONIC_FYL2XP1:
            break;
        case ZYDIS_MNEMONIC_GETSEC:
            break;
        case ZYDIS_MNEMONIC_GF2P8AFFINEINVQB:
            break;
        case ZYDIS_MNEMONIC_GF2P8AFFINEQB:
            break;
        case ZYDIS_MNEMONIC_GF2P8MULB:
            break;
        case ZYDIS_MNEMONIC_HADDPD:
            break;
        case ZYDIS_MNEMONIC_HADDPS:
            break;
        case ZYDIS_MNEMONIC_HLT:
            break;
        case ZYDIS_MNEMONIC_HSUBPD:
            break;
        case ZYDIS_MNEMONIC_HSUBPS:
            break;
        case ZYDIS_MNEMONIC_IDIV:
            break;
        case ZYDIS_MNEMONIC_IMUL:
            break;
        case ZYDIS_MNEMONIC_IN:
            break;
        case ZYDIS_MNEMONIC_INC:
            break;
        case ZYDIS_MNEMONIC_INCSSPD:
            break;
        case ZYDIS_MNEMONIC_INCSSPQ:
            break;
        case ZYDIS_MNEMONIC_INSB:
            break;
        case ZYDIS_MNEMONIC_INSD:
            break;
        case ZYDIS_MNEMONIC_INSERTPS:
            break;
        case ZYDIS_MNEMONIC_INSERTQ:
            break;
        case ZYDIS_MNEMONIC_INSW:
            break;
        case ZYDIS_MNEMONIC_INT:
            break;
        case ZYDIS_MNEMONIC_INT1:
            break;
        case ZYDIS_MNEMONIC_INT3:
            break;
        case ZYDIS_MNEMONIC_INTO:
            break;
        case ZYDIS_MNEMONIC_INVD:
            break;
        case ZYDIS_MNEMONIC_INVEPT:
            break;
        case ZYDIS_MNEMONIC_INVLPG:
            break;
        case ZYDIS_MNEMONIC_INVLPGA:
            break;
        case ZYDIS_MNEMONIC_INVPCID:
            break;
        case ZYDIS_MNEMONIC_INVVPID:
            break;
        case ZYDIS_MNEMONIC_IRET:
            break;
        case ZYDIS_MNEMONIC_IRETD:
            break;
        case ZYDIS_MNEMONIC_IRETQ:
            break;
        case ZYDIS_MNEMONIC_JB:
            break;
        case ZYDIS_MNEMONIC_JBE:
            break;
        case ZYDIS_MNEMONIC_JCXZ:
            break;
        case ZYDIS_MNEMONIC_JECXZ:
            break;
        case ZYDIS_MNEMONIC_JKNZD:
            break;
        case ZYDIS_MNEMONIC_JKZD:
            break;
        case ZYDIS_MNEMONIC_JL:
            break;
        case ZYDIS_MNEMONIC_JLE:
            break;
        case ZYDIS_MNEMONIC_JMP:
            break;
        case ZYDIS_MNEMONIC_JNB:
            break;
        case ZYDIS_MNEMONIC_JNBE:
            break;
        case ZYDIS_MNEMONIC_JNL:
            break;
        case ZYDIS_MNEMONIC_JNLE:
            break;
        case ZYDIS_MNEMONIC_JNO:
            break;
        case ZYDIS_MNEMONIC_JNP:
            break;
        case ZYDIS_MNEMONIC_JNS:
            break;
        case ZYDIS_MNEMONIC_JNZ:
            break;
        case ZYDIS_MNEMONIC_JO:
            break;
        case ZYDIS_MNEMONIC_JP:
            break;
        case ZYDIS_MNEMONIC_JRCXZ:
            break;
        case ZYDIS_MNEMONIC_JS:
            break;
        case ZYDIS_MNEMONIC_JZ:
            break;
        case ZYDIS_MNEMONIC_KADDB:
            break;
        case ZYDIS_MNEMONIC_KADDD:
            break;
        case ZYDIS_MNEMONIC_KADDQ:
            break;
        case ZYDIS_MNEMONIC_KADDW:
            break;
        case ZYDIS_MNEMONIC_KAND:
            break;
        case ZYDIS_MNEMONIC_KANDB:
            break;
        case ZYDIS_MNEMONIC_KANDD:
            break;
        case ZYDIS_MNEMONIC_KANDN:
            break;
        case ZYDIS_MNEMONIC_KANDNB:
            break;
        case ZYDIS_MNEMONIC_KANDND:
            break;
        case ZYDIS_MNEMONIC_KANDNQ:
            break;
        case ZYDIS_MNEMONIC_KANDNR:
            break;
        case ZYDIS_MNEMONIC_KANDNW:
            break;
        case ZYDIS_MNEMONIC_KANDQ:
            break;
        case ZYDIS_MNEMONIC_KANDW:
            break;
        case ZYDIS_MNEMONIC_KCONCATH:
            break;
        case ZYDIS_MNEMONIC_KCONCATL:
            break;
        case ZYDIS_MNEMONIC_KEXTRACT:
            break;
        case ZYDIS_MNEMONIC_KMERGE2L1H:
            break;
        case ZYDIS_MNEMONIC_KMERGE2L1L:
            break;
        case ZYDIS_MNEMONIC_KMOV:
            break;
        case ZYDIS_MNEMONIC_KMOVB:
            break;
        case ZYDIS_MNEMONIC_KMOVD:
            break;
        case ZYDIS_MNEMONIC_KMOVQ:
            break;
        case ZYDIS_MNEMONIC_KMOVW:
            break;
        case ZYDIS_MNEMONIC_KNOT:
            break;
        case ZYDIS_MNEMONIC_KNOTB:
            break;
        case ZYDIS_MNEMONIC_KNOTD:
            break;
        case ZYDIS_MNEMONIC_KNOTQ:
            break;
        case ZYDIS_MNEMONIC_KNOTW:
            break;
        case ZYDIS_MNEMONIC_KOR:
            break;
        case ZYDIS_MNEMONIC_KORB:
            break;
        case ZYDIS_MNEMONIC_KORD:
            break;
        case ZYDIS_MNEMONIC_KORQ:
            break;
        case ZYDIS_MNEMONIC_KORTEST:
            break;
        case ZYDIS_MNEMONIC_KORTESTB:
            break;
        case ZYDIS_MNEMONIC_KORTESTD:
            break;
        case ZYDIS_MNEMONIC_KORTESTQ:
            break;
        case ZYDIS_MNEMONIC_KORTESTW:
            break;
        case ZYDIS_MNEMONIC_KORW:
            break;
        case ZYDIS_MNEMONIC_KSHIFTLB:
            break;
        case ZYDIS_MNEMONIC_KSHIFTLD:
            break;
        case ZYDIS_MNEMONIC_KSHIFTLQ:
            break;
        case ZYDIS_MNEMONIC_KSHIFTLW:
            break;
        case ZYDIS_MNEMONIC_KSHIFTRB:
            break;
        case ZYDIS_MNEMONIC_KSHIFTRD:
            break;
        case ZYDIS_MNEMONIC_KSHIFTRQ:
            break;
        case ZYDIS_MNEMONIC_KSHIFTRW:
            break;
        case ZYDIS_MNEMONIC_KTESTB:
            break;
        case ZYDIS_MNEMONIC_KTESTD:
            break;
        case ZYDIS_MNEMONIC_KTESTQ:
            break;
        case ZYDIS_MNEMONIC_KTESTW:
            break;
        case ZYDIS_MNEMONIC_KUNPCKBW:
            break;
        case ZYDIS_MNEMONIC_KUNPCKDQ:
            break;
        case ZYDIS_MNEMONIC_KUNPCKWD:
            break;
        case ZYDIS_MNEMONIC_KXNOR:
            break;
        case ZYDIS_MNEMONIC_KXNORB:
            break;
        case ZYDIS_MNEMONIC_KXNORD:
            break;
        case ZYDIS_MNEMONIC_KXNORQ:
            break;
        case ZYDIS_MNEMONIC_KXNORW:
            break;
        case ZYDIS_MNEMONIC_KXOR:
            break;
        case ZYDIS_MNEMONIC_KXORB:
            break;
        case ZYDIS_MNEMONIC_KXORD:
            break;
        case ZYDIS_MNEMONIC_KXORQ:
            break;
        case ZYDIS_MNEMONIC_KXORW:
            break;
        case ZYDIS_MNEMONIC_LAHF:
            break;
        case ZYDIS_MNEMONIC_LAR:
            break;
        case ZYDIS_MNEMONIC_LDDQU:
            break;
        case ZYDIS_MNEMONIC_LDMXCSR:
            break;
        case ZYDIS_MNEMONIC_LDS:
            break;
        case ZYDIS_MNEMONIC_LEA:
            break;
        case ZYDIS_MNEMONIC_LEAVE:
            break;
        case ZYDIS_MNEMONIC_LES:
            break;
        case ZYDIS_MNEMONIC_LFENCE:
            break;
        case ZYDIS_MNEMONIC_LFS:
            break;
        case ZYDIS_MNEMONIC_LGDT:
            break;
        case ZYDIS_MNEMONIC_LGS:
            break;
        case ZYDIS_MNEMONIC_LIDT:
            break;
        case ZYDIS_MNEMONIC_LLDT:
            break;
        case ZYDIS_MNEMONIC_LLWPCB:
            break;
        case ZYDIS_MNEMONIC_LMSW:
            break;
        case ZYDIS_MNEMONIC_LODSB:
            break;
        case ZYDIS_MNEMONIC_LODSD:
            break;
        case ZYDIS_MNEMONIC_LODSQ:
            break;
        case ZYDIS_MNEMONIC_LODSW:
            break;
        case ZYDIS_MNEMONIC_LOOP:
            break;
        case ZYDIS_MNEMONIC_LOOPE:
            break;
        case ZYDIS_MNEMONIC_LOOPNE:
            break;
        case ZYDIS_MNEMONIC_LSL:
            break;
        case ZYDIS_MNEMONIC_LSS:
            break;
        case ZYDIS_MNEMONIC_LTR:
            break;
        case ZYDIS_MNEMONIC_LWPINS:
            break;
        case ZYDIS_MNEMONIC_LWPVAL:
            break;
        case ZYDIS_MNEMONIC_LZCNT:
            break;
        case ZYDIS_MNEMONIC_MASKMOVDQU:
            break;
        case ZYDIS_MNEMONIC_MASKMOVQ:
            break;
        case ZYDIS_MNEMONIC_MAXPD:
            break;
        case ZYDIS_MNEMONIC_MAXPS:
            break;
        case ZYDIS_MNEMONIC_MAXSD:
            break;
        case ZYDIS_MNEMONIC_MAXSS:
            break;
        case ZYDIS_MNEMONIC_MFENCE:
            break;
        case ZYDIS_MNEMONIC_MINPD:
            break;
        case ZYDIS_MNEMONIC_MINPS:
            break;
        case ZYDIS_MNEMONIC_MINSD:
            break;
        case ZYDIS_MNEMONIC_MINSS:
            break;
        case ZYDIS_MNEMONIC_MONITOR:
            break;
        case ZYDIS_MNEMONIC_MONITORX:
            break;
        case ZYDIS_MNEMONIC_MONTMUL:
            break;
        case ZYDIS_MNEMONIC_MOV:
            break;
        case ZYDIS_MNEMONIC_MOVAPD:
            break;
        case ZYDIS_MNEMONIC_MOVAPS:
            break;
        case ZYDIS_MNEMONIC_MOVBE:
            break;
        case ZYDIS_MNEMONIC_MOVD:
            break;
        case ZYDIS_MNEMONIC_MOVDDUP:
            break;
        case ZYDIS_MNEMONIC_MOVDIR64B:
            break;
        case ZYDIS_MNEMONIC_MOVDIRI:
            break;
        case ZYDIS_MNEMONIC_MOVDQ2Q:
            break;
        case ZYDIS_MNEMONIC_MOVDQA:
            break;
        case ZYDIS_MNEMONIC_MOVDQU:
            break;
        case ZYDIS_MNEMONIC_MOVHLPS:
            break;
        case ZYDIS_MNEMONIC_MOVHPD:
            break;
        case ZYDIS_MNEMONIC_MOVHPS:
            break;
        case ZYDIS_MNEMONIC_MOVLHPS:
            break;
        case ZYDIS_MNEMONIC_MOVLPD:
            break;
        case ZYDIS_MNEMONIC_MOVLPS:
            break;
        case ZYDIS_MNEMONIC_MOVMSKPD:
            break;
        case ZYDIS_MNEMONIC_MOVMSKPS:
            break;
        case ZYDIS_MNEMONIC_MOVNTDQ:
            break;
        case ZYDIS_MNEMONIC_MOVNTDQA:
            break;
        case ZYDIS_MNEMONIC_MOVNTI:
            break;
        case ZYDIS_MNEMONIC_MOVNTPD:
            break;
        case ZYDIS_MNEMONIC_MOVNTPS:
            break;
        case ZYDIS_MNEMONIC_MOVNTQ:
            break;
        case ZYDIS_MNEMONIC_MOVNTSD:
            break;
        case ZYDIS_MNEMONIC_MOVNTSS:
            break;
        case ZYDIS_MNEMONIC_MOVQ:
            break;
        case ZYDIS_MNEMONIC_MOVQ2DQ:
            break;
        case ZYDIS_MNEMONIC_MOVSB:
            break;
        case ZYDIS_MNEMONIC_MOVSD:
            break;
        case ZYDIS_MNEMONIC_MOVSHDUP:
            break;
        case ZYDIS_MNEMONIC_MOVSLDUP:
            break;
        case ZYDIS_MNEMONIC_MOVSQ:
            break;
        case ZYDIS_MNEMONIC_MOVSS:
            break;
        case ZYDIS_MNEMONIC_MOVSW:
            break;
        case ZYDIS_MNEMONIC_MOVSX:
            break;
        case ZYDIS_MNEMONIC_MOVSXD:
            break;
        case ZYDIS_MNEMONIC_MOVUPD:
            break;
        case ZYDIS_MNEMONIC_MOVUPS:
            break;
        case ZYDIS_MNEMONIC_MOVZX:
            break;
        case ZYDIS_MNEMONIC_MPSADBW:
            break;
        case ZYDIS_MNEMONIC_MUL:
            break;
        case ZYDIS_MNEMONIC_MULPD:
            break;
        case ZYDIS_MNEMONIC_MULPS:
            break;
        case ZYDIS_MNEMONIC_MULSD:
            break;
        case ZYDIS_MNEMONIC_MULSS:
            break;
        case ZYDIS_MNEMONIC_MULX:
            break;
        case ZYDIS_MNEMONIC_MWAIT:
            break;
        case ZYDIS_MNEMONIC_MWAITX:
            break;
        case ZYDIS_MNEMONIC_NEG:
            break;
        case ZYDIS_MNEMONIC_NOP:
            break;
        case ZYDIS_MNEMONIC_NOT:
            break;
        case ZYDIS_MNEMONIC_OR:
            break;
        case ZYDIS_MNEMONIC_ORPD:
            break;
        case ZYDIS_MNEMONIC_ORPS:
            break;
        case ZYDIS_MNEMONIC_OUT:
            break;
        case ZYDIS_MNEMONIC_OUTSB:
            break;
        case ZYDIS_MNEMONIC_OUTSD:
            break;
        case ZYDIS_MNEMONIC_OUTSW:
            break;
        case ZYDIS_MNEMONIC_PABSB:
            break;
        case ZYDIS_MNEMONIC_PABSD:
            break;
        case ZYDIS_MNEMONIC_PABSW:
            break;
        case ZYDIS_MNEMONIC_PACKSSDW:
            break;
        case ZYDIS_MNEMONIC_PACKSSWB:
            break;
        case ZYDIS_MNEMONIC_PACKUSDW:
            break;
        case ZYDIS_MNEMONIC_PACKUSWB:
            break;
        case ZYDIS_MNEMONIC_PADDB:
            break;
        case ZYDIS_MNEMONIC_PADDD:
            break;
        case ZYDIS_MNEMONIC_PADDQ:
            break;
        case ZYDIS_MNEMONIC_PADDSB:
            break;
        case ZYDIS_MNEMONIC_PADDSW:
            break;
        case ZYDIS_MNEMONIC_PADDUSB:
            break;
        case ZYDIS_MNEMONIC_PADDUSW:
            break;
        case ZYDIS_MNEMONIC_PADDW:
            break;
        case ZYDIS_MNEMONIC_PALIGNR:
            break;
        case ZYDIS_MNEMONIC_PAND:
            break;
        case ZYDIS_MNEMONIC_PANDN:
            break;
        case ZYDIS_MNEMONIC_PAUSE:
            break;
        case ZYDIS_MNEMONIC_PAVGB:
            break;
        case ZYDIS_MNEMONIC_PAVGUSB:
            break;
        case ZYDIS_MNEMONIC_PAVGW:
            break;
        case ZYDIS_MNEMONIC_PBLENDVB:
            break;
        case ZYDIS_MNEMONIC_PBLENDW:
            break;
        case ZYDIS_MNEMONIC_PCLMULQDQ:
            break;
        case ZYDIS_MNEMONIC_PCMPEQB:
            break;
        case ZYDIS_MNEMONIC_PCMPEQD:
            break;
        case ZYDIS_MNEMONIC_PCMPEQQ:
            break;
        case ZYDIS_MNEMONIC_PCMPEQW:
            break;
        case ZYDIS_MNEMONIC_PCMPESTRI:
            break;
        case ZYDIS_MNEMONIC_PCMPESTRM:
            break;
        case ZYDIS_MNEMONIC_PCMPGTB:
            break;
        case ZYDIS_MNEMONIC_PCMPGTD:
            break;
        case ZYDIS_MNEMONIC_PCMPGTQ:
            break;
        case ZYDIS_MNEMONIC_PCMPGTW:
            break;
        case ZYDIS_MNEMONIC_PCMPISTRI:
            break;
        case ZYDIS_MNEMONIC_PCMPISTRM:
            break;
        case ZYDIS_MNEMONIC_PCONFIG:
            break;
        case ZYDIS_MNEMONIC_PDEP:
            break;
        case ZYDIS_MNEMONIC_PEXT:
            break;
        case ZYDIS_MNEMONIC_PEXTRB:
            break;
        case ZYDIS_MNEMONIC_PEXTRD:
            break;
        case ZYDIS_MNEMONIC_PEXTRQ:
            break;
        case ZYDIS_MNEMONIC_PEXTRW:
            break;
        case ZYDIS_MNEMONIC_PF2ID:
            break;
        case ZYDIS_MNEMONIC_PF2IW:
            break;
        case ZYDIS_MNEMONIC_PFACC:
            break;
        case ZYDIS_MNEMONIC_PFADD:
            break;
        case ZYDIS_MNEMONIC_PFCMPEQ:
            break;
        case ZYDIS_MNEMONIC_PFCMPGE:
            break;
        case ZYDIS_MNEMONIC_PFCMPGT:
            break;
        case ZYDIS_MNEMONIC_PFCPIT1:
            break;
        case ZYDIS_MNEMONIC_PFMAX:
            break;
        case ZYDIS_MNEMONIC_PFMIN:
            break;
        case ZYDIS_MNEMONIC_PFMUL:
            break;
        case ZYDIS_MNEMONIC_PFNACC:
            break;
        case ZYDIS_MNEMONIC_PFPNACC:
            break;
        case ZYDIS_MNEMONIC_PFRCP:
            break;
        case ZYDIS_MNEMONIC_PFRCPIT2:
            break;
        case ZYDIS_MNEMONIC_PFRSQIT1:
            break;
        case ZYDIS_MNEMONIC_PFSQRT:
            break;
        case ZYDIS_MNEMONIC_PFSUB:
            break;
        case ZYDIS_MNEMONIC_PFSUBR:
            break;
        case ZYDIS_MNEMONIC_PHADDD:
            break;
        case ZYDIS_MNEMONIC_PHADDSW:
            break;
        case ZYDIS_MNEMONIC_PHADDW:
            break;
        case ZYDIS_MNEMONIC_PHMINPOSUW:
            break;
        case ZYDIS_MNEMONIC_PHSUBD:
            break;
        case ZYDIS_MNEMONIC_PHSUBSW:
            break;
        case ZYDIS_MNEMONIC_PHSUBW:
            break;
        case ZYDIS_MNEMONIC_PI2FD:
            break;
        case ZYDIS_MNEMONIC_PI2FW:
            break;
        case ZYDIS_MNEMONIC_PINSRB:
            break;
        case ZYDIS_MNEMONIC_PINSRD:
            break;
        case ZYDIS_MNEMONIC_PINSRQ:
            break;
        case ZYDIS_MNEMONIC_PINSRW:
            break;
        case ZYDIS_MNEMONIC_PMADDUBSW:
            break;
        case ZYDIS_MNEMONIC_PMADDWD:
            break;
        case ZYDIS_MNEMONIC_PMAXSB:
            break;
        case ZYDIS_MNEMONIC_PMAXSD:
            break;
        case ZYDIS_MNEMONIC_PMAXSW:
            break;
        case ZYDIS_MNEMONIC_PMAXUB:
            break;
        case ZYDIS_MNEMONIC_PMAXUD:
            break;
        case ZYDIS_MNEMONIC_PMAXUW:
            break;
        case ZYDIS_MNEMONIC_PMINSB:
            break;
        case ZYDIS_MNEMONIC_PMINSD:
            break;
        case ZYDIS_MNEMONIC_PMINSW:
            break;
        case ZYDIS_MNEMONIC_PMINUB:
            break;
        case ZYDIS_MNEMONIC_PMINUD:
            break;
        case ZYDIS_MNEMONIC_PMINUW:
            break;
        case ZYDIS_MNEMONIC_PMOVMSKB:
            break;
        case ZYDIS_MNEMONIC_PMOVSXBD:
            break;
        case ZYDIS_MNEMONIC_PMOVSXBQ:
            break;
        case ZYDIS_MNEMONIC_PMOVSXBW:
            break;
        case ZYDIS_MNEMONIC_PMOVSXDQ:
            break;
        case ZYDIS_MNEMONIC_PMOVSXWD:
            break;
        case ZYDIS_MNEMONIC_PMOVSXWQ:
            break;
        case ZYDIS_MNEMONIC_PMOVZXBD:
            break;
        case ZYDIS_MNEMONIC_PMOVZXBQ:
            break;
        case ZYDIS_MNEMONIC_PMOVZXBW:
            break;
        case ZYDIS_MNEMONIC_PMOVZXDQ:
            break;
        case ZYDIS_MNEMONIC_PMOVZXWD:
            break;
        case ZYDIS_MNEMONIC_PMOVZXWQ:
            break;
        case ZYDIS_MNEMONIC_PMULDQ:
            break;
        case ZYDIS_MNEMONIC_PMULHRSW:
            break;
        case ZYDIS_MNEMONIC_PMULHRW:
            break;
        case ZYDIS_MNEMONIC_PMULHUW:
            break;
        case ZYDIS_MNEMONIC_PMULHW:
            break;
        case ZYDIS_MNEMONIC_PMULLD:
            break;
        case ZYDIS_MNEMONIC_PMULLW:
            break;
        case ZYDIS_MNEMONIC_PMULUDQ:
            break;
        case ZYDIS_MNEMONIC_POP:
            break;
        case ZYDIS_MNEMONIC_POPA:
            break;
        case ZYDIS_MNEMONIC_POPAD:
            break;
        case ZYDIS_MNEMONIC_POPCNT:
            break;
        case ZYDIS_MNEMONIC_POPF:
            break;
        case ZYDIS_MNEMONIC_POPFD:
            break;
        case ZYDIS_MNEMONIC_POPFQ:
            break;
        case ZYDIS_MNEMONIC_POR:
            break;
        case ZYDIS_MNEMONIC_PREFETCH:
            break;
        case ZYDIS_MNEMONIC_PREFETCHNTA:
            break;
        case ZYDIS_MNEMONIC_PREFETCHT0:
            break;
        case ZYDIS_MNEMONIC_PREFETCHT1:
            break;
        case ZYDIS_MNEMONIC_PREFETCHT2:
            break;
        case ZYDIS_MNEMONIC_PREFETCHW:
            break;
        case ZYDIS_MNEMONIC_PREFETCHWT1:
            break;
        case ZYDIS_MNEMONIC_PSADBW:
            break;
        case ZYDIS_MNEMONIC_PSHUFB:
            break;
        case ZYDIS_MNEMONIC_PSHUFD:
            break;
        case ZYDIS_MNEMONIC_PSHUFHW:
            break;
        case ZYDIS_MNEMONIC_PSHUFLW:
            break;
        case ZYDIS_MNEMONIC_PSHUFW:
            break;
        case ZYDIS_MNEMONIC_PSIGNB:
            break;
        case ZYDIS_MNEMONIC_PSIGND:
            break;
        case ZYDIS_MNEMONIC_PSIGNW:
            break;
        case ZYDIS_MNEMONIC_PSLLD:
            break;
        case ZYDIS_MNEMONIC_PSLLDQ:
            break;
        case ZYDIS_MNEMONIC_PSLLQ:
            break;
        case ZYDIS_MNEMONIC_PSLLW:
            break;
        case ZYDIS_MNEMONIC_PSRAD:
            break;
        case ZYDIS_MNEMONIC_PSRAW:
            break;
        case ZYDIS_MNEMONIC_PSRLD:
            break;
        case ZYDIS_MNEMONIC_PSRLDQ:
            break;
        case ZYDIS_MNEMONIC_PSRLQ:
            break;
        case ZYDIS_MNEMONIC_PSRLW:
            break;
        case ZYDIS_MNEMONIC_PSUBB:
            break;
        case ZYDIS_MNEMONIC_PSUBD:
            break;
        case ZYDIS_MNEMONIC_PSUBQ:
            break;
        case ZYDIS_MNEMONIC_PSUBSB:
            break;
        case ZYDIS_MNEMONIC_PSUBSW:
            break;
        case ZYDIS_MNEMONIC_PSUBUSB:
            break;
        case ZYDIS_MNEMONIC_PSUBUSW:
            break;
        case ZYDIS_MNEMONIC_PSUBW:
            break;
        case ZYDIS_MNEMONIC_PSWAPD:
            break;
        case ZYDIS_MNEMONIC_PTEST:
            break;
        case ZYDIS_MNEMONIC_PTWRITE:
            break;
        case ZYDIS_MNEMONIC_PUNPCKHBW:
            break;
        case ZYDIS_MNEMONIC_PUNPCKHDQ:
            break;
        case ZYDIS_MNEMONIC_PUNPCKHQDQ:
            break;
        case ZYDIS_MNEMONIC_PUNPCKHWD:
            break;
        case ZYDIS_MNEMONIC_PUNPCKLBW:
            break;
        case ZYDIS_MNEMONIC_PUNPCKLDQ:
            break;
        case ZYDIS_MNEMONIC_PUNPCKLQDQ:
            break;
        case ZYDIS_MNEMONIC_PUNPCKLWD:
            break;
        case ZYDIS_MNEMONIC_PUSH:
            break;
        case ZYDIS_MNEMONIC_PUSHA:
            break;
        case ZYDIS_MNEMONIC_PUSHAD:
            break;
        case ZYDIS_MNEMONIC_PUSHF:
            break;
        case ZYDIS_MNEMONIC_PUSHFD:
            break;
        case ZYDIS_MNEMONIC_PUSHFQ:
            break;
        case ZYDIS_MNEMONIC_PXOR:
            break;
        case ZYDIS_MNEMONIC_RCL:
            break;
        case ZYDIS_MNEMONIC_RCPPS:
            break;
        case ZYDIS_MNEMONIC_RCPSS:
            break;
        case ZYDIS_MNEMONIC_RCR:
            break;
        case ZYDIS_MNEMONIC_RDFSBASE:
            break;
        case ZYDIS_MNEMONIC_RDGSBASE:
            break;
        case ZYDIS_MNEMONIC_RDMSR:
            break;
        case ZYDIS_MNEMONIC_RDPID:
            break;
        case ZYDIS_MNEMONIC_RDPKRU:
            break;
        case ZYDIS_MNEMONIC_RDPMC:
            break;
        case ZYDIS_MNEMONIC_RDPRU:
            break;
        case ZYDIS_MNEMONIC_RDRAND:
            break;
        case ZYDIS_MNEMONIC_RDSEED:
            break;
        case ZYDIS_MNEMONIC_RDSSPD:
            break;
        case ZYDIS_MNEMONIC_RDSSPQ:
            break;
        case ZYDIS_MNEMONIC_RDTSC:
            break;
        case ZYDIS_MNEMONIC_RDTSCP:
            break;
        case ZYDIS_MNEMONIC_RET:
            break;
        case ZYDIS_MNEMONIC_ROL:
            break;
        case ZYDIS_MNEMONIC_ROR:
            break;
        case ZYDIS_MNEMONIC_RORX:
            break;
        case ZYDIS_MNEMONIC_ROUNDPD:
            break;
        case ZYDIS_MNEMONIC_ROUNDPS:
            break;
        case ZYDIS_MNEMONIC_ROUNDSD:
            break;
        case ZYDIS_MNEMONIC_ROUNDSS:
            break;
        case ZYDIS_MNEMONIC_RSM:
            break;
        case ZYDIS_MNEMONIC_RSQRTPS:
            break;
        case ZYDIS_MNEMONIC_RSQRTSS:
            break;
        case ZYDIS_MNEMONIC_RSTORSSP:
            break;
        case ZYDIS_MNEMONIC_SAHF:
            break;
        case ZYDIS_MNEMONIC_SALC:
            break;
        case ZYDIS_MNEMONIC_SAR:
            break;
        case ZYDIS_MNEMONIC_SARX:
            break;
        case ZYDIS_MNEMONIC_SAVEPREVSSP:
            break;
        case ZYDIS_MNEMONIC_SBB:
            break;
        case ZYDIS_MNEMONIC_SCASB:
            break;
        case ZYDIS_MNEMONIC_SCASD:
            break;
        case ZYDIS_MNEMONIC_SCASQ:
            break;
        case ZYDIS_MNEMONIC_SCASW:
            break;
        case ZYDIS_MNEMONIC_SETB:
            break;
        case ZYDIS_MNEMONIC_SETBE:
            break;
        case ZYDIS_MNEMONIC_SETL:
            break;
        case ZYDIS_MNEMONIC_SETLE:
            break;
        case ZYDIS_MNEMONIC_SETNB:
            break;
        case ZYDIS_MNEMONIC_SETNBE:
            break;
        case ZYDIS_MNEMONIC_SETNL:
            break;
        case ZYDIS_MNEMONIC_SETNLE:
            break;
        case ZYDIS_MNEMONIC_SETNO:
            break;
        case ZYDIS_MNEMONIC_SETNP:
            break;
        case ZYDIS_MNEMONIC_SETNS:
            break;
        case ZYDIS_MNEMONIC_SETNZ:
            break;
        case ZYDIS_MNEMONIC_SETO:
            break;
        case ZYDIS_MNEMONIC_SETP:
            break;
        case ZYDIS_MNEMONIC_SETS:
            break;
        case ZYDIS_MNEMONIC_SETSSBSY:
            break;
        case ZYDIS_MNEMONIC_SETZ:
            break;
        case ZYDIS_MNEMONIC_SFENCE:
            break;
        case ZYDIS_MNEMONIC_SGDT:
            break;
        case ZYDIS_MNEMONIC_SHA1MSG1:
            break;
        case ZYDIS_MNEMONIC_SHA1MSG2:
            break;
        case ZYDIS_MNEMONIC_SHA1NEXTE:
            break;
        case ZYDIS_MNEMONIC_SHA1RNDS4:
            break;
        case ZYDIS_MNEMONIC_SHA256MSG1:
            break;
        case ZYDIS_MNEMONIC_SHA256MSG2:
            break;
        case ZYDIS_MNEMONIC_SHA256RNDS2:
            break;
        case ZYDIS_MNEMONIC_SHL:
            break;
        case ZYDIS_MNEMONIC_SHLD:
            break;
        case ZYDIS_MNEMONIC_SHLX:
            break;
        case ZYDIS_MNEMONIC_SHR:
            break;
        case ZYDIS_MNEMONIC_SHRD:
            break;
        case ZYDIS_MNEMONIC_SHRX:
            break;
        case ZYDIS_MNEMONIC_SHUFPD:
            break;
        case ZYDIS_MNEMONIC_SHUFPS:
            break;
        case ZYDIS_MNEMONIC_SIDT:
            break;
        case ZYDIS_MNEMONIC_SKINIT:
            break;
        case ZYDIS_MNEMONIC_SLDT:
            break;
        case ZYDIS_MNEMONIC_SLWPCB:
            break;
        case ZYDIS_MNEMONIC_SMSW:
            break;
        case ZYDIS_MNEMONIC_SPFLT:
            break;
        case ZYDIS_MNEMONIC_SQRTPD:
            break;
        case ZYDIS_MNEMONIC_SQRTPS:
            break;
        case ZYDIS_MNEMONIC_SQRTSD:
            break;
        case ZYDIS_MNEMONIC_SQRTSS:
            break;
        case ZYDIS_MNEMONIC_STAC:
            break;
        case ZYDIS_MNEMONIC_STC:
            break;
        case ZYDIS_MNEMONIC_STD:
            break;
        case ZYDIS_MNEMONIC_STGI:
            break;
        case ZYDIS_MNEMONIC_STI:
            break;
        case ZYDIS_MNEMONIC_STMXCSR:
            break;
        case ZYDIS_MNEMONIC_STOSB:
            break;
        case ZYDIS_MNEMONIC_STOSD:
            break;
        case ZYDIS_MNEMONIC_STOSQ:
            break;
        case ZYDIS_MNEMONIC_STOSW:
            break;
        case ZYDIS_MNEMONIC_STR:
            break;
        case ZYDIS_MNEMONIC_SUB:
            break;
        case ZYDIS_MNEMONIC_SUBPD:
            break;
        case ZYDIS_MNEMONIC_SUBPS:
            break;
        case ZYDIS_MNEMONIC_SUBSD:
            break;
        case ZYDIS_MNEMONIC_SUBSS:
            break;
        case ZYDIS_MNEMONIC_SWAPGS:
            break;
        case ZYDIS_MNEMONIC_SYSCALL:
            break;
        case ZYDIS_MNEMONIC_SYSENTER:
            break;
        case ZYDIS_MNEMONIC_SYSEXIT:
            break;
        case ZYDIS_MNEMONIC_SYSRET:
            break;
        case ZYDIS_MNEMONIC_T1MSKC:
            break;
        case ZYDIS_MNEMONIC_TEST:
            break;
        case ZYDIS_MNEMONIC_TPAUSE:
            break;
        case ZYDIS_MNEMONIC_TZCNT:
            break;
        case ZYDIS_MNEMONIC_TZCNTI:
            break;
        case ZYDIS_MNEMONIC_TZMSK:
            break;
        case ZYDIS_MNEMONIC_UCOMISD:
            break;
        case ZYDIS_MNEMONIC_UCOMISS:
            break;
        case ZYDIS_MNEMONIC_UD0:
            break;
        case ZYDIS_MNEMONIC_UD1:
            break;
        case ZYDIS_MNEMONIC_UD2:
            break;
        case ZYDIS_MNEMONIC_UMONITOR:
            break;
        case ZYDIS_MNEMONIC_UMWAIT:
            break;
        case ZYDIS_MNEMONIC_UNPCKHPD:
            break;
        case ZYDIS_MNEMONIC_UNPCKHPS:
            break;
        case ZYDIS_MNEMONIC_UNPCKLPD:
            break;
        case ZYDIS_MNEMONIC_UNPCKLPS:
            break;
        case ZYDIS_MNEMONIC_V4FMADDPS:
            break;
        case ZYDIS_MNEMONIC_V4FMADDSS:
            break;
        case ZYDIS_MNEMONIC_V4FNMADDPS:
            break;
        case ZYDIS_MNEMONIC_V4FNMADDSS:
            break;
        case ZYDIS_MNEMONIC_VADDNPD:
            break;
        case ZYDIS_MNEMONIC_VADDNPS:
            break;
        case ZYDIS_MNEMONIC_VADDPD:
            break;
        case ZYDIS_MNEMONIC_VADDPS:
            break;
        case ZYDIS_MNEMONIC_VADDSD:
            break;
        case ZYDIS_MNEMONIC_VADDSETSPS:
            break;
        case ZYDIS_MNEMONIC_VADDSS:
            break;
        case ZYDIS_MNEMONIC_VADDSUBPD:
            break;
        case ZYDIS_MNEMONIC_VADDSUBPS:
            break;
        case ZYDIS_MNEMONIC_VAESDEC:
            break;
        case ZYDIS_MNEMONIC_VAESDECLAST:
            break;
        case ZYDIS_MNEMONIC_VAESENC:
            break;
        case ZYDIS_MNEMONIC_VAESENCLAST:
            break;
        case ZYDIS_MNEMONIC_VAESIMC:
            break;
        case ZYDIS_MNEMONIC_VAESKEYGENASSIST:
            break;
        case ZYDIS_MNEMONIC_VALIGND:
            break;
        case ZYDIS_MNEMONIC_VALIGNQ:
            break;
        case ZYDIS_MNEMONIC_VANDNPD:
            break;
        case ZYDIS_MNEMONIC_VANDNPS:
            break;
        case ZYDIS_MNEMONIC_VANDPD:
            break;
        case ZYDIS_MNEMONIC_VANDPS:
            break;
        case ZYDIS_MNEMONIC_VBLENDMPD:
            break;
        case ZYDIS_MNEMONIC_VBLENDMPS:
            break;
        case ZYDIS_MNEMONIC_VBLENDPD:
            break;
        case ZYDIS_MNEMONIC_VBLENDPS:
            break;
        case ZYDIS_MNEMONIC_VBLENDVPD:
            break;
        case ZYDIS_MNEMONIC_VBLENDVPS:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTF128:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTF32X2:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTF32X4:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTF32X8:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTF64X2:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTF64X4:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTI128:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTI32X2:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTI32X4:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTI32X8:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTI64X2:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTI64X4:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTSD:
            break;
        case ZYDIS_MNEMONIC_VBROADCASTSS:
            break;
        case ZYDIS_MNEMONIC_VCMPPD:
            break;
        case ZYDIS_MNEMONIC_VCMPPS:
            break;
        case ZYDIS_MNEMONIC_VCMPSD:
            break;
        case ZYDIS_MNEMONIC_VCMPSS:
            break;
        case ZYDIS_MNEMONIC_VCOMISD:
            break;
        case ZYDIS_MNEMONIC_VCOMISS:
            break;
        case ZYDIS_MNEMONIC_VCOMPRESSPD:
            break;
        case ZYDIS_MNEMONIC_VCOMPRESSPS:
            break;
        case ZYDIS_MNEMONIC_VCVTDQ2PD:
            break;
        case ZYDIS_MNEMONIC_VCVTDQ2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTFXPNTDQ2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTFXPNTPD2DQ:
            break;
        case ZYDIS_MNEMONIC_VCVTFXPNTPD2UDQ:
            break;
        case ZYDIS_MNEMONIC_VCVTFXPNTPS2DQ:
            break;
        case ZYDIS_MNEMONIC_VCVTFXPNTPS2UDQ:
            break;
        case ZYDIS_MNEMONIC_VCVTFXPNTUDQ2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTNE2PS2BF16:
            break;
        case ZYDIS_MNEMONIC_VCVTNEPS2BF16:
            break;
        case ZYDIS_MNEMONIC_VCVTPD2DQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPD2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTPD2QQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPD2UDQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPD2UQQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPH2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTPS2DQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPS2PD:
            break;
        case ZYDIS_MNEMONIC_VCVTPS2PH:
            break;
        case ZYDIS_MNEMONIC_VCVTPS2QQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPS2UDQ:
            break;
        case ZYDIS_MNEMONIC_VCVTPS2UQQ:
            break;
        case ZYDIS_MNEMONIC_VCVTQQ2PD:
            break;
        case ZYDIS_MNEMONIC_VCVTQQ2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTSD2SI:
            break;
        case ZYDIS_MNEMONIC_VCVTSD2SS:
            break;
        case ZYDIS_MNEMONIC_VCVTSD2USI:
            break;
        case ZYDIS_MNEMONIC_VCVTSI2SD:
            break;
        case ZYDIS_MNEMONIC_VCVTSI2SS:
            break;
        case ZYDIS_MNEMONIC_VCVTSS2SD:
            break;
        case ZYDIS_MNEMONIC_VCVTSS2SI:
            break;
        case ZYDIS_MNEMONIC_VCVTSS2USI:
            break;
        case ZYDIS_MNEMONIC_VCVTTPD2DQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPD2QQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPD2UDQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPD2UQQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPS2DQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPS2QQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPS2UDQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTPS2UQQ:
            break;
        case ZYDIS_MNEMONIC_VCVTTSD2SI:
            break;
        case ZYDIS_MNEMONIC_VCVTTSD2USI:
            break;
        case ZYDIS_MNEMONIC_VCVTTSS2SI:
            break;
        case ZYDIS_MNEMONIC_VCVTTSS2USI:
            break;
        case ZYDIS_MNEMONIC_VCVTUDQ2PD:
            break;
        case ZYDIS_MNEMONIC_VCVTUDQ2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTUQQ2PD:
            break;
        case ZYDIS_MNEMONIC_VCVTUQQ2PS:
            break;
        case ZYDIS_MNEMONIC_VCVTUSI2SD:
            break;
        case ZYDIS_MNEMONIC_VCVTUSI2SS:
            break;
        case ZYDIS_MNEMONIC_VDBPSADBW:
            break;
        case ZYDIS_MNEMONIC_VDIVPD:
            break;
        case ZYDIS_MNEMONIC_VDIVPS:
            break;
        case ZYDIS_MNEMONIC_VDIVSD:
            break;
        case ZYDIS_MNEMONIC_VDIVSS:
            break;
        case ZYDIS_MNEMONIC_VDPBF16PS:
            break;
        case ZYDIS_MNEMONIC_VDPPD:
            break;
        case ZYDIS_MNEMONIC_VDPPS:
            break;
        case ZYDIS_MNEMONIC_VERR:
            break;
        case ZYDIS_MNEMONIC_VERW:
            break;
        case ZYDIS_MNEMONIC_VEXP223PS:
            break;
        case ZYDIS_MNEMONIC_VEXP2PD:
            break;
        case ZYDIS_MNEMONIC_VEXP2PS:
            break;
        case ZYDIS_MNEMONIC_VEXPANDPD:
            break;
        case ZYDIS_MNEMONIC_VEXPANDPS:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTF128:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTF32X4:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTF32X8:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTF64X2:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTF64X4:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTI128:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTI32X4:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTI32X8:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTI64X2:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTI64X4:
            break;
        case ZYDIS_MNEMONIC_VEXTRACTPS:
            break;
        case ZYDIS_MNEMONIC_VFIXUPIMMPD:
            break;
        case ZYDIS_MNEMONIC_VFIXUPIMMPS:
            break;
        case ZYDIS_MNEMONIC_VFIXUPIMMSD:
            break;
        case ZYDIS_MNEMONIC_VFIXUPIMMSS:
            break;
        case ZYDIS_MNEMONIC_VFIXUPNANPD:
            break;
        case ZYDIS_MNEMONIC_VFIXUPNANPS:
            break;
        case ZYDIS_MNEMONIC_VFMADD132PD:
            break;
        case ZYDIS_MNEMONIC_VFMADD132PS:
            break;
        case ZYDIS_MNEMONIC_VFMADD132SD:
            break;
        case ZYDIS_MNEMONIC_VFMADD132SS:
            break;
        case ZYDIS_MNEMONIC_VFMADD213PD:
            break;
        case ZYDIS_MNEMONIC_VFMADD213PS:
            break;
        case ZYDIS_MNEMONIC_VFMADD213SD:
            break;
        case ZYDIS_MNEMONIC_VFMADD213SS:
            break;
        case ZYDIS_MNEMONIC_VFMADD231PD:
            break;
        case ZYDIS_MNEMONIC_VFMADD231PS:
            break;
        case ZYDIS_MNEMONIC_VFMADD231SD:
            break;
        case ZYDIS_MNEMONIC_VFMADD231SS:
            break;
        case ZYDIS_MNEMONIC_VFMADD233PS:
            break;
        case ZYDIS_MNEMONIC_VFMADDPD:
            break;
        case ZYDIS_MNEMONIC_VFMADDPS:
            break;
        case ZYDIS_MNEMONIC_VFMADDSD:
            break;
        case ZYDIS_MNEMONIC_VFMADDSS:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUB132PD:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUB132PS:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUB213PD:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUB213PS:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUB231PD:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUB231PS:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUBPD:
            break;
        case ZYDIS_MNEMONIC_VFMADDSUBPS:
            break;
        case ZYDIS_MNEMONIC_VFMSUB132PD:
            break;
        case ZYDIS_MNEMONIC_VFMSUB132PS:
            break;
        case ZYDIS_MNEMONIC_VFMSUB132SD:
            break;
        case ZYDIS_MNEMONIC_VFMSUB132SS:
            break;
        case ZYDIS_MNEMONIC_VFMSUB213PD:
            break;
        case ZYDIS_MNEMONIC_VFMSUB213PS:
            break;
        case ZYDIS_MNEMONIC_VFMSUB213SD:
            break;
        case ZYDIS_MNEMONIC_VFMSUB213SS:
            break;
        case ZYDIS_MNEMONIC_VFMSUB231PD:
            break;
        case ZYDIS_MNEMONIC_VFMSUB231PS:
            break;
        case ZYDIS_MNEMONIC_VFMSUB231SD:
            break;
        case ZYDIS_MNEMONIC_VFMSUB231SS:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADD132PD:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADD132PS:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADD213PD:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADD213PS:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADD231PD:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADD231PS:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADDPD:
            break;
        case ZYDIS_MNEMONIC_VFMSUBADDPS:
            break;
        case ZYDIS_MNEMONIC_VFMSUBPD:
            break;
        case ZYDIS_MNEMONIC_VFMSUBPS:
            break;
        case ZYDIS_MNEMONIC_VFMSUBSD:
            break;
        case ZYDIS_MNEMONIC_VFMSUBSS:
            break;
        case ZYDIS_MNEMONIC_VFNMADD132PD:
            break;
        case ZYDIS_MNEMONIC_VFNMADD132PS:
            break;
        case ZYDIS_MNEMONIC_VFNMADD132SD:
            break;
        case ZYDIS_MNEMONIC_VFNMADD132SS:
            break;
        case ZYDIS_MNEMONIC_VFNMADD213PD:
            break;
        case ZYDIS_MNEMONIC_VFNMADD213PS:
            break;
        case ZYDIS_MNEMONIC_VFNMADD213SD:
            break;
        case ZYDIS_MNEMONIC_VFNMADD213SS:
            break;
        case ZYDIS_MNEMONIC_VFNMADD231PD:
            break;
        case ZYDIS_MNEMONIC_VFNMADD231PS:
            break;
        case ZYDIS_MNEMONIC_VFNMADD231SD:
            break;
        case ZYDIS_MNEMONIC_VFNMADD231SS:
            break;
        case ZYDIS_MNEMONIC_VFNMADDPD:
            break;
        case ZYDIS_MNEMONIC_VFNMADDPS:
            break;
        case ZYDIS_MNEMONIC_VFNMADDSD:
            break;
        case ZYDIS_MNEMONIC_VFNMADDSS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB132PD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB132PS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB132SD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB132SS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB213PD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB213PS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB213SD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB213SS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB231PD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB231PS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB231SD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUB231SS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUBPD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUBPS:
            break;
        case ZYDIS_MNEMONIC_VFNMSUBSD:
            break;
        case ZYDIS_MNEMONIC_VFNMSUBSS:
            break;
        case ZYDIS_MNEMONIC_VFPCLASSPD:
            break;
        case ZYDIS_MNEMONIC_VFPCLASSPS:
            break;
        case ZYDIS_MNEMONIC_VFPCLASSSD:
            break;
        case ZYDIS_MNEMONIC_VFPCLASSSS:
            break;
        case ZYDIS_MNEMONIC_VFRCZPD:
            break;
        case ZYDIS_MNEMONIC_VFRCZPS:
            break;
        case ZYDIS_MNEMONIC_VFRCZSD:
            break;
        case ZYDIS_MNEMONIC_VFRCZSS:
            break;
        case ZYDIS_MNEMONIC_VGATHERDPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERDPS:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF0DPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF0DPS:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF0HINTDPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF0HINTDPS:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF0QPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF0QPS:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF1DPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF1DPS:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF1QPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERPF1QPS:
            break;
        case ZYDIS_MNEMONIC_VGATHERQPD:
            break;
        case ZYDIS_MNEMONIC_VGATHERQPS:
            break;
        case ZYDIS_MNEMONIC_VGETEXPPD:
            break;
        case ZYDIS_MNEMONIC_VGETEXPPS:
            break;
        case ZYDIS_MNEMONIC_VGETEXPSD:
            break;
        case ZYDIS_MNEMONIC_VGETEXPSS:
            break;
        case ZYDIS_MNEMONIC_VGETMANTPD:
            break;
        case ZYDIS_MNEMONIC_VGETMANTPS:
            break;
        case ZYDIS_MNEMONIC_VGETMANTSD:
            break;
        case ZYDIS_MNEMONIC_VGETMANTSS:
            break;
        case ZYDIS_MNEMONIC_VGF2P8AFFINEINVQB:
            break;
        case ZYDIS_MNEMONIC_VGF2P8AFFINEQB:
            break;
        case ZYDIS_MNEMONIC_VGF2P8MULB:
            break;
        case ZYDIS_MNEMONIC_VGMAXABSPS:
            break;
        case ZYDIS_MNEMONIC_VGMAXPD:
            break;
        case ZYDIS_MNEMONIC_VGMAXPS:
            break;
        case ZYDIS_MNEMONIC_VGMINPD:
            break;
        case ZYDIS_MNEMONIC_VGMINPS:
            break;
        case ZYDIS_MNEMONIC_VHADDPD:
            break;
        case ZYDIS_MNEMONIC_VHADDPS:
            break;
        case ZYDIS_MNEMONIC_VHSUBPD:
            break;
        case ZYDIS_MNEMONIC_VHSUBPS:
            break;
        case ZYDIS_MNEMONIC_VINSERTF128:
            break;
        case ZYDIS_MNEMONIC_VINSERTF32X4:
            break;
        case ZYDIS_MNEMONIC_VINSERTF32X8:
            break;
        case ZYDIS_MNEMONIC_VINSERTF64X2:
            break;
        case ZYDIS_MNEMONIC_VINSERTF64X4:
            break;
        case ZYDIS_MNEMONIC_VINSERTI128:
            break;
        case ZYDIS_MNEMONIC_VINSERTI32X4:
            break;
        case ZYDIS_MNEMONIC_VINSERTI32X8:
            break;
        case ZYDIS_MNEMONIC_VINSERTI64X2:
            break;
        case ZYDIS_MNEMONIC_VINSERTI64X4:
            break;
        case ZYDIS_MNEMONIC_VINSERTPS:
            break;
        case ZYDIS_MNEMONIC_VLDDQU:
            break;
        case ZYDIS_MNEMONIC_VLDMXCSR:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKHD:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKHPD:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKHPS:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKHQ:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKLD:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKLPD:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKLPS:
            break;
        case ZYDIS_MNEMONIC_VLOADUNPACKLQ:
            break;
        case ZYDIS_MNEMONIC_VLOG2PS:
            break;
        case ZYDIS_MNEMONIC_VMASKMOVDQU:
            break;
        case ZYDIS_MNEMONIC_VMASKMOVPD:
            break;
        case ZYDIS_MNEMONIC_VMASKMOVPS:
            break;
        case ZYDIS_MNEMONIC_VMAXPD:
            break;
        case ZYDIS_MNEMONIC_VMAXPS:
            break;
        case ZYDIS_MNEMONIC_VMAXSD:
            break;
        case ZYDIS_MNEMONIC_VMAXSS:
            break;
        case ZYDIS_MNEMONIC_VMCALL:
            break;
        case ZYDIS_MNEMONIC_VMCLEAR:
            break;
        case ZYDIS_MNEMONIC_VMFUNC:
            break;
        case ZYDIS_MNEMONIC_VMINPD:
            break;
        case ZYDIS_MNEMONIC_VMINPS:
            break;
        case ZYDIS_MNEMONIC_VMINSD:
            break;
        case ZYDIS_MNEMONIC_VMINSS:
            break;
        case ZYDIS_MNEMONIC_VMLAUNCH:
            break;
        case ZYDIS_MNEMONIC_VMLOAD:
            break;
        case ZYDIS_MNEMONIC_VMMCALL:
            break;
        case ZYDIS_MNEMONIC_VMOVAPD:
            break;
        case ZYDIS_MNEMONIC_VMOVAPS:
            break;
        case ZYDIS_MNEMONIC_VMOVD:
            break;
        case ZYDIS_MNEMONIC_VMOVDDUP:
            break;
        case ZYDIS_MNEMONIC_VMOVDQA:
            break;
        case ZYDIS_MNEMONIC_VMOVDQA32:
            break;
        case ZYDIS_MNEMONIC_VMOVDQA64:
            break;
        case ZYDIS_MNEMONIC_VMOVDQU:
            break;
        case ZYDIS_MNEMONIC_VMOVDQU16:
            break;
        case ZYDIS_MNEMONIC_VMOVDQU32:
            break;
        case ZYDIS_MNEMONIC_VMOVDQU64:
            break;
        case ZYDIS_MNEMONIC_VMOVDQU8:
            break;
        case ZYDIS_MNEMONIC_VMOVHLPS:
            break;
        case ZYDIS_MNEMONIC_VMOVHPD:
            break;
        case ZYDIS_MNEMONIC_VMOVHPS:
            break;
        case ZYDIS_MNEMONIC_VMOVLHPS:
            break;
        case ZYDIS_MNEMONIC_VMOVLPD:
            break;
        case ZYDIS_MNEMONIC_VMOVLPS:
            break;
        case ZYDIS_MNEMONIC_VMOVMSKPD:
            break;
        case ZYDIS_MNEMONIC_VMOVMSKPS:
            break;
        case ZYDIS_MNEMONIC_VMOVNRAPD:
            break;
        case ZYDIS_MNEMONIC_VMOVNRAPS:
            break;
        case ZYDIS_MNEMONIC_VMOVNRNGOAPD:
            break;
        case ZYDIS_MNEMONIC_VMOVNRNGOAPS:
            break;
        case ZYDIS_MNEMONIC_VMOVNTDQ:
            break;
        case ZYDIS_MNEMONIC_VMOVNTDQA:
            break;
        case ZYDIS_MNEMONIC_VMOVNTPD:
            break;
        case ZYDIS_MNEMONIC_VMOVNTPS:
            break;
        case ZYDIS_MNEMONIC_VMOVQ:
            break;
        case ZYDIS_MNEMONIC_VMOVSD:
            break;
        case ZYDIS_MNEMONIC_VMOVSHDUP:
            break;
        case ZYDIS_MNEMONIC_VMOVSLDUP:
            break;
        case ZYDIS_MNEMONIC_VMOVSS:
            break;
        case ZYDIS_MNEMONIC_VMOVUPD:
            break;
        case ZYDIS_MNEMONIC_VMOVUPS:
            break;
        case ZYDIS_MNEMONIC_VMPSADBW:
            break;
        case ZYDIS_MNEMONIC_VMPTRLD:
            break;
        case ZYDIS_MNEMONIC_VMPTRST:
            break;
        case ZYDIS_MNEMONIC_VMREAD:
            break;
        case ZYDIS_MNEMONIC_VMRESUME:
            break;
        case ZYDIS_MNEMONIC_VMRUN:
            break;
        case ZYDIS_MNEMONIC_VMSAVE:
            break;
        case ZYDIS_MNEMONIC_VMULPD:
            break;
        case ZYDIS_MNEMONIC_VMULPS:
            break;
        case ZYDIS_MNEMONIC_VMULSD:
            break;
        case ZYDIS_MNEMONIC_VMULSS:
            break;
        case ZYDIS_MNEMONIC_VMWRITE:
            break;
        case ZYDIS_MNEMONIC_VMXOFF:
            break;
        case ZYDIS_MNEMONIC_VMXON:
            break;
        case ZYDIS_MNEMONIC_VORPD:
            break;
        case ZYDIS_MNEMONIC_VORPS:
            break;
        case ZYDIS_MNEMONIC_VP2INTERSECTD:
            break;
        case ZYDIS_MNEMONIC_VP2INTERSECTQ:
            break;
        case ZYDIS_MNEMONIC_VP4DPWSSD:
            break;
        case ZYDIS_MNEMONIC_VP4DPWSSDS:
            break;
        case ZYDIS_MNEMONIC_VPABSB:
            break;
        case ZYDIS_MNEMONIC_VPABSD:
            break;
        case ZYDIS_MNEMONIC_VPABSQ:
            break;
        case ZYDIS_MNEMONIC_VPABSW:
            break;
        case ZYDIS_MNEMONIC_VPACKSSDW:
            break;
        case ZYDIS_MNEMONIC_VPACKSSWB:
            break;
        case ZYDIS_MNEMONIC_VPACKSTOREHD:
            break;
        case ZYDIS_MNEMONIC_VPACKSTOREHPD:
            break;
        case ZYDIS_MNEMONIC_VPACKSTOREHPS:
            break;
        case ZYDIS_MNEMONIC_VPACKSTOREHQ:
            break;
        case ZYDIS_MNEMONIC_VPACKSTORELD:
            break;
        case ZYDIS_MNEMONIC_VPACKSTORELPD:
            break;
        case ZYDIS_MNEMONIC_VPACKSTORELPS:
            break;
        case ZYDIS_MNEMONIC_VPACKSTORELQ:
            break;
        case ZYDIS_MNEMONIC_VPACKUSDW:
            break;
        case ZYDIS_MNEMONIC_VPACKUSWB:
            break;
        case ZYDIS_MNEMONIC_VPADCD:
            break;
        case ZYDIS_MNEMONIC_VPADDB:
            break;
        case ZYDIS_MNEMONIC_VPADDD:
            break;
        case ZYDIS_MNEMONIC_VPADDQ:
            break;
        case ZYDIS_MNEMONIC_VPADDSB:
            break;
        case ZYDIS_MNEMONIC_VPADDSETCD:
            break;
        case ZYDIS_MNEMONIC_VPADDSETSD:
            break;
        case ZYDIS_MNEMONIC_VPADDSW:
            break;
        case ZYDIS_MNEMONIC_VPADDUSB:
            break;
        case ZYDIS_MNEMONIC_VPADDUSW:
            break;
        case ZYDIS_MNEMONIC_VPADDW:
            break;
        case ZYDIS_MNEMONIC_VPALIGNR:
            break;
        case ZYDIS_MNEMONIC_VPAND:
            break;
        case ZYDIS_MNEMONIC_VPANDD:
            break;
        case ZYDIS_MNEMONIC_VPANDN:
            break;
        case ZYDIS_MNEMONIC_VPANDND:
            break;
        case ZYDIS_MNEMONIC_VPANDNQ:
            break;
        case ZYDIS_MNEMONIC_VPANDQ:
            break;
        case ZYDIS_MNEMONIC_VPAVGB:
            break;
        case ZYDIS_MNEMONIC_VPAVGW:
            break;
        case ZYDIS_MNEMONIC_VPBLENDD:
            break;
        case ZYDIS_MNEMONIC_VPBLENDMB:
            break;
        case ZYDIS_MNEMONIC_VPBLENDMD:
            break;
        case ZYDIS_MNEMONIC_VPBLENDMQ:
            break;
        case ZYDIS_MNEMONIC_VPBLENDMW:
            break;
        case ZYDIS_MNEMONIC_VPBLENDVB:
            break;
        case ZYDIS_MNEMONIC_VPBLENDW:
            break;
        case ZYDIS_MNEMONIC_VPBROADCASTB:
            break;
        case ZYDIS_MNEMONIC_VPBROADCASTD:
            break;
        case ZYDIS_MNEMONIC_VPBROADCASTMB2Q:
            break;
        case ZYDIS_MNEMONIC_VPBROADCASTMW2D:
            break;
        case ZYDIS_MNEMONIC_VPBROADCASTQ:
            break;
        case ZYDIS_MNEMONIC_VPBROADCASTW:
            break;
        case ZYDIS_MNEMONIC_VPCLMULQDQ:
            break;
        case ZYDIS_MNEMONIC_VPCMOV:
            break;
        case ZYDIS_MNEMONIC_VPCMPB:
            break;
        case ZYDIS_MNEMONIC_VPCMPD:
            break;
        case ZYDIS_MNEMONIC_VPCMPEQB:
            break;
        case ZYDIS_MNEMONIC_VPCMPEQD:
            break;
        case ZYDIS_MNEMONIC_VPCMPEQQ:
            break;
        case ZYDIS_MNEMONIC_VPCMPEQW:
            break;
        case ZYDIS_MNEMONIC_VPCMPESTRI:
            break;
        case ZYDIS_MNEMONIC_VPCMPESTRM:
            break;
        case ZYDIS_MNEMONIC_VPCMPGTB:
            break;
        case ZYDIS_MNEMONIC_VPCMPGTD:
            break;
        case ZYDIS_MNEMONIC_VPCMPGTQ:
            break;
        case ZYDIS_MNEMONIC_VPCMPGTW:
            break;
        case ZYDIS_MNEMONIC_VPCMPISTRI:
            break;
        case ZYDIS_MNEMONIC_VPCMPISTRM:
            break;
        case ZYDIS_MNEMONIC_VPCMPLTD:
            break;
        case ZYDIS_MNEMONIC_VPCMPQ:
            break;
        case ZYDIS_MNEMONIC_VPCMPUB:
            break;
        case ZYDIS_MNEMONIC_VPCMPUD:
            break;
        case ZYDIS_MNEMONIC_VPCMPUQ:
            break;
        case ZYDIS_MNEMONIC_VPCMPUW:
            break;
        case ZYDIS_MNEMONIC_VPCMPW:
            break;
        case ZYDIS_MNEMONIC_VPCOMB:
            break;
        case ZYDIS_MNEMONIC_VPCOMD:
            break;
        case ZYDIS_MNEMONIC_VPCOMPRESSB:
            break;
        case ZYDIS_MNEMONIC_VPCOMPRESSD:
            break;
        case ZYDIS_MNEMONIC_VPCOMPRESSQ:
            break;
        case ZYDIS_MNEMONIC_VPCOMPRESSW:
            break;
        case ZYDIS_MNEMONIC_VPCOMQ:
            break;
        case ZYDIS_MNEMONIC_VPCOMUB:
            break;
        case ZYDIS_MNEMONIC_VPCOMUD:
            break;
        case ZYDIS_MNEMONIC_VPCOMUQ:
            break;
        case ZYDIS_MNEMONIC_VPCOMUW:
            break;
        case ZYDIS_MNEMONIC_VPCOMW:
            break;
        case ZYDIS_MNEMONIC_VPCONFLICTD:
            break;
        case ZYDIS_MNEMONIC_VPCONFLICTQ:
            break;
        case ZYDIS_MNEMONIC_VPDPBUSD:
            break;
        case ZYDIS_MNEMONIC_VPDPBUSDS:
            break;
        case ZYDIS_MNEMONIC_VPDPWSSD:
            break;
        case ZYDIS_MNEMONIC_VPDPWSSDS:
            break;
        case ZYDIS_MNEMONIC_VPERM2F128:
            break;
        case ZYDIS_MNEMONIC_VPERM2I128:
            break;
        case ZYDIS_MNEMONIC_VPERMB:
            break;
        case ZYDIS_MNEMONIC_VPERMD:
            break;
        case ZYDIS_MNEMONIC_VPERMF32X4:
            break;
        case ZYDIS_MNEMONIC_VPERMI2B:
            break;
        case ZYDIS_MNEMONIC_VPERMI2D:
            break;
        case ZYDIS_MNEMONIC_VPERMI2PD:
            break;
        case ZYDIS_MNEMONIC_VPERMI2PS:
            break;
        case ZYDIS_MNEMONIC_VPERMI2Q:
            break;
        case ZYDIS_MNEMONIC_VPERMI2W:
            break;
        case ZYDIS_MNEMONIC_VPERMIL2PD:
            break;
        case ZYDIS_MNEMONIC_VPERMIL2PS:
            break;
        case ZYDIS_MNEMONIC_VPERMILPD:
            break;
        case ZYDIS_MNEMONIC_VPERMILPS:
            break;
        case ZYDIS_MNEMONIC_VPERMPD:
            break;
        case ZYDIS_MNEMONIC_VPERMPS:
            break;
        case ZYDIS_MNEMONIC_VPERMQ:
            break;
        case ZYDIS_MNEMONIC_VPERMT2B:
            break;
        case ZYDIS_MNEMONIC_VPERMT2D:
            break;
        case ZYDIS_MNEMONIC_VPERMT2PD:
            break;
        case ZYDIS_MNEMONIC_VPERMT2PS:
            break;
        case ZYDIS_MNEMONIC_VPERMT2Q:
            break;
        case ZYDIS_MNEMONIC_VPERMT2W:
            break;
        case ZYDIS_MNEMONIC_VPERMW:
            break;
        case ZYDIS_MNEMONIC_VPEXPANDB:
            break;
        case ZYDIS_MNEMONIC_VPEXPANDD:
            break;
        case ZYDIS_MNEMONIC_VPEXPANDQ:
            break;
        case ZYDIS_MNEMONIC_VPEXPANDW:
            break;
        case ZYDIS_MNEMONIC_VPEXTRB:
            break;
        case ZYDIS_MNEMONIC_VPEXTRD:
            break;
        case ZYDIS_MNEMONIC_VPEXTRQ:
            break;
        case ZYDIS_MNEMONIC_VPEXTRW:
            break;
        case ZYDIS_MNEMONIC_VPGATHERDD:
            break;
        case ZYDIS_MNEMONIC_VPGATHERDQ:
            break;
        case ZYDIS_MNEMONIC_VPGATHERQD:
            break;
        case ZYDIS_MNEMONIC_VPGATHERQQ:
            break;
        case ZYDIS_MNEMONIC_VPHADDBD:
            break;
        case ZYDIS_MNEMONIC_VPHADDBQ:
            break;
        case ZYDIS_MNEMONIC_VPHADDBW:
            break;
        case ZYDIS_MNEMONIC_VPHADDD:
            break;
        case ZYDIS_MNEMONIC_VPHADDDQ:
            break;
        case ZYDIS_MNEMONIC_VPHADDSW:
            break;
        case ZYDIS_MNEMONIC_VPHADDUBD:
            break;
        case ZYDIS_MNEMONIC_VPHADDUBQ:
            break;
        case ZYDIS_MNEMONIC_VPHADDUBW:
            break;
        case ZYDIS_MNEMONIC_VPHADDUDQ:
            break;
        case ZYDIS_MNEMONIC_VPHADDUWD:
            break;
        case ZYDIS_MNEMONIC_VPHADDUWQ:
            break;
        case ZYDIS_MNEMONIC_VPHADDW:
            break;
        case ZYDIS_MNEMONIC_VPHADDWD:
            break;
        case ZYDIS_MNEMONIC_VPHADDWQ:
            break;
        case ZYDIS_MNEMONIC_VPHMINPOSUW:
            break;
        case ZYDIS_MNEMONIC_VPHSUBBW:
            break;
        case ZYDIS_MNEMONIC_VPHSUBD:
            break;
        case ZYDIS_MNEMONIC_VPHSUBDQ:
            break;
        case ZYDIS_MNEMONIC_VPHSUBSW:
            break;
        case ZYDIS_MNEMONIC_VPHSUBW:
            break;
        case ZYDIS_MNEMONIC_VPHSUBWD:
            break;
        case ZYDIS_MNEMONIC_VPINSRB:
            break;
        case ZYDIS_MNEMONIC_VPINSRD:
            break;
        case ZYDIS_MNEMONIC_VPINSRQ:
            break;
        case ZYDIS_MNEMONIC_VPINSRW:
            break;
        case ZYDIS_MNEMONIC_VPLZCNTD:
            break;
        case ZYDIS_MNEMONIC_VPLZCNTQ:
            break;
        case ZYDIS_MNEMONIC_VPMACSDD:
            break;
        case ZYDIS_MNEMONIC_VPMACSDQH:
            break;
        case ZYDIS_MNEMONIC_VPMACSDQL:
            break;
        case ZYDIS_MNEMONIC_VPMACSSDD:
            break;
        case ZYDIS_MNEMONIC_VPMACSSDQH:
            break;
        case ZYDIS_MNEMONIC_VPMACSSDQL:
            break;
        case ZYDIS_MNEMONIC_VPMACSSWD:
            break;
        case ZYDIS_MNEMONIC_VPMACSSWW:
            break;
        case ZYDIS_MNEMONIC_VPMACSWD:
            break;
        case ZYDIS_MNEMONIC_VPMACSWW:
            break;
        case ZYDIS_MNEMONIC_VPMADCSSWD:
            break;
        case ZYDIS_MNEMONIC_VPMADCSWD:
            break;
        case ZYDIS_MNEMONIC_VPMADD231D:
            break;
        case ZYDIS_MNEMONIC_VPMADD233D:
            break;
        case ZYDIS_MNEMONIC_VPMADD52HUQ:
            break;
        case ZYDIS_MNEMONIC_VPMADD52LUQ:
            break;
        case ZYDIS_MNEMONIC_VPMADDUBSW:
            break;
        case ZYDIS_MNEMONIC_VPMADDWD:
            break;
        case ZYDIS_MNEMONIC_VPMASKMOVD:
            break;
        case ZYDIS_MNEMONIC_VPMASKMOVQ:
            break;
        case ZYDIS_MNEMONIC_VPMAXSB:
            break;
        case ZYDIS_MNEMONIC_VPMAXSD:
            break;
        case ZYDIS_MNEMONIC_VPMAXSQ:
            break;
        case ZYDIS_MNEMONIC_VPMAXSW:
            break;
        case ZYDIS_MNEMONIC_VPMAXUB:
            break;
        case ZYDIS_MNEMONIC_VPMAXUD:
            break;
        case ZYDIS_MNEMONIC_VPMAXUQ:
            break;
        case ZYDIS_MNEMONIC_VPMAXUW:
            break;
        case ZYDIS_MNEMONIC_VPMINSB:
            break;
        case ZYDIS_MNEMONIC_VPMINSD:
            break;
        case ZYDIS_MNEMONIC_VPMINSQ:
            break;
        case ZYDIS_MNEMONIC_VPMINSW:
            break;
        case ZYDIS_MNEMONIC_VPMINUB:
            break;
        case ZYDIS_MNEMONIC_VPMINUD:
            break;
        case ZYDIS_MNEMONIC_VPMINUQ:
            break;
        case ZYDIS_MNEMONIC_VPMINUW:
            break;
        case ZYDIS_MNEMONIC_VPMOVB2M:
            break;
        case ZYDIS_MNEMONIC_VPMOVD2M:
            break;
        case ZYDIS_MNEMONIC_VPMOVDB:
            break;
        case ZYDIS_MNEMONIC_VPMOVDW:
            break;
        case ZYDIS_MNEMONIC_VPMOVM2B:
            break;
        case ZYDIS_MNEMONIC_VPMOVM2D:
            break;
        case ZYDIS_MNEMONIC_VPMOVM2Q:
            break;
        case ZYDIS_MNEMONIC_VPMOVM2W:
            break;
        case ZYDIS_MNEMONIC_VPMOVMSKB:
            break;
        case ZYDIS_MNEMONIC_VPMOVQ2M:
            break;
        case ZYDIS_MNEMONIC_VPMOVQB:
            break;
        case ZYDIS_MNEMONIC_VPMOVQD:
            break;
        case ZYDIS_MNEMONIC_VPMOVQW:
            break;
        case ZYDIS_MNEMONIC_VPMOVSDB:
            break;
        case ZYDIS_MNEMONIC_VPMOVSDW:
            break;
        case ZYDIS_MNEMONIC_VPMOVSQB:
            break;
        case ZYDIS_MNEMONIC_VPMOVSQD:
            break;
        case ZYDIS_MNEMONIC_VPMOVSQW:
            break;
        case ZYDIS_MNEMONIC_VPMOVSWB:
            break;
        case ZYDIS_MNEMONIC_VPMOVSXBD:
            break;
        case ZYDIS_MNEMONIC_VPMOVSXBQ:
            break;
        case ZYDIS_MNEMONIC_VPMOVSXBW:
            break;
        case ZYDIS_MNEMONIC_VPMOVSXDQ:
            break;
        case ZYDIS_MNEMONIC_VPMOVSXWD:
            break;
        case ZYDIS_MNEMONIC_VPMOVSXWQ:
            break;
        case ZYDIS_MNEMONIC_VPMOVUSDB:
            break;
        case ZYDIS_MNEMONIC_VPMOVUSDW:
            break;
        case ZYDIS_MNEMONIC_VPMOVUSQB:
            break;
        case ZYDIS_MNEMONIC_VPMOVUSQD:
            break;
        case ZYDIS_MNEMONIC_VPMOVUSQW:
            break;
        case ZYDIS_MNEMONIC_VPMOVUSWB:
            break;
        case ZYDIS_MNEMONIC_VPMOVW2M:
            break;
        case ZYDIS_MNEMONIC_VPMOVWB:
            break;
        case ZYDIS_MNEMONIC_VPMOVZXBD:
            break;
        case ZYDIS_MNEMONIC_VPMOVZXBQ:
            break;
        case ZYDIS_MNEMONIC_VPMOVZXBW:
            break;
        case ZYDIS_MNEMONIC_VPMOVZXDQ:
            break;
        case ZYDIS_MNEMONIC_VPMOVZXWD:
            break;
        case ZYDIS_MNEMONIC_VPMOVZXWQ:
            break;
        case ZYDIS_MNEMONIC_VPMULDQ:
            break;
        case ZYDIS_MNEMONIC_VPMULHD:
            break;
        case ZYDIS_MNEMONIC_VPMULHRSW:
            break;
        case ZYDIS_MNEMONIC_VPMULHUD:
            break;
        case ZYDIS_MNEMONIC_VPMULHUW:
            break;
        case ZYDIS_MNEMONIC_VPMULHW:
            break;
        case ZYDIS_MNEMONIC_VPMULLD:
            break;
        case ZYDIS_MNEMONIC_VPMULLQ:
            break;
        case ZYDIS_MNEMONIC_VPMULLW:
            break;
        case ZYDIS_MNEMONIC_VPMULTISHIFTQB:
            break;
        case ZYDIS_MNEMONIC_VPMULUDQ:
            break;
        case ZYDIS_MNEMONIC_VPOPCNTB:
            break;
        case ZYDIS_MNEMONIC_VPOPCNTD:
            break;
        case ZYDIS_MNEMONIC_VPOPCNTQ:
            break;
        case ZYDIS_MNEMONIC_VPOPCNTW:
            break;
        case ZYDIS_MNEMONIC_VPOR:
            break;
        case ZYDIS_MNEMONIC_VPORD:
            break;
        case ZYDIS_MNEMONIC_VPORQ:
            break;
        case ZYDIS_MNEMONIC_VPPERM:
            break;
        case ZYDIS_MNEMONIC_VPREFETCH0:
            break;
        case ZYDIS_MNEMONIC_VPREFETCH1:
            break;
        case ZYDIS_MNEMONIC_VPREFETCH2:
            break;
        case ZYDIS_MNEMONIC_VPREFETCHE0:
            break;
        case ZYDIS_MNEMONIC_VPREFETCHE1:
            break;
        case ZYDIS_MNEMONIC_VPREFETCHE2:
            break;
        case ZYDIS_MNEMONIC_VPREFETCHENTA:
            break;
        case ZYDIS_MNEMONIC_VPREFETCHNTA:
            break;
        case ZYDIS_MNEMONIC_VPROLD:
            break;
        case ZYDIS_MNEMONIC_VPROLQ:
            break;
        case ZYDIS_MNEMONIC_VPROLVD:
            break;
        case ZYDIS_MNEMONIC_VPROLVQ:
            break;
        case ZYDIS_MNEMONIC_VPRORD:
            break;
        case ZYDIS_MNEMONIC_VPRORQ:
            break;
        case ZYDIS_MNEMONIC_VPRORVD:
            break;
        case ZYDIS_MNEMONIC_VPRORVQ:
            break;
        case ZYDIS_MNEMONIC_VPROTB:
            break;
        case ZYDIS_MNEMONIC_VPROTD:
            break;
        case ZYDIS_MNEMONIC_VPROTQ:
            break;
        case ZYDIS_MNEMONIC_VPROTW:
            break;
        case ZYDIS_MNEMONIC_VPSADBW:
            break;
        case ZYDIS_MNEMONIC_VPSBBD:
            break;
        case ZYDIS_MNEMONIC_VPSBBRD:
            break;
        case ZYDIS_MNEMONIC_VPSCATTERDD:
            break;
        case ZYDIS_MNEMONIC_VPSCATTERDQ:
            break;
        case ZYDIS_MNEMONIC_VPSCATTERQD:
            break;
        case ZYDIS_MNEMONIC_VPSCATTERQQ:
            break;
        case ZYDIS_MNEMONIC_VPSHAB:
            break;
        case ZYDIS_MNEMONIC_VPSHAD:
            break;
        case ZYDIS_MNEMONIC_VPSHAQ:
            break;
        case ZYDIS_MNEMONIC_VPSHAW:
            break;
        case ZYDIS_MNEMONIC_VPSHLB:
            break;
        case ZYDIS_MNEMONIC_VPSHLD:
            break;
        case ZYDIS_MNEMONIC_VPSHLDD:
            break;
        case ZYDIS_MNEMONIC_VPSHLDQ:
            break;
        case ZYDIS_MNEMONIC_VPSHLDVD:
            break;
        case ZYDIS_MNEMONIC_VPSHLDVQ:
            break;
        case ZYDIS_MNEMONIC_VPSHLDVW:
            break;
        case ZYDIS_MNEMONIC_VPSHLDW:
            break;
        case ZYDIS_MNEMONIC_VPSHLQ:
            break;
        case ZYDIS_MNEMONIC_VPSHLW:
            break;
        case ZYDIS_MNEMONIC_VPSHRDD:
            break;
        case ZYDIS_MNEMONIC_VPSHRDQ:
            break;
        case ZYDIS_MNEMONIC_VPSHRDVD:
            break;
        case ZYDIS_MNEMONIC_VPSHRDVQ:
            break;
        case ZYDIS_MNEMONIC_VPSHRDVW:
            break;
        case ZYDIS_MNEMONIC_VPSHRDW:
            break;
        case ZYDIS_MNEMONIC_VPSHUFB:
            break;
        case ZYDIS_MNEMONIC_VPSHUFBITQMB:
            break;
        case ZYDIS_MNEMONIC_VPSHUFD:
            break;
        case ZYDIS_MNEMONIC_VPSHUFHW:
            break;
        case ZYDIS_MNEMONIC_VPSHUFLW:
            break;
        case ZYDIS_MNEMONIC_VPSIGNB:
            break;
        case ZYDIS_MNEMONIC_VPSIGND:
            break;
        case ZYDIS_MNEMONIC_VPSIGNW:
            break;
        case ZYDIS_MNEMONIC_VPSLLD:
            break;
        case ZYDIS_MNEMONIC_VPSLLDQ:
            break;
        case ZYDIS_MNEMONIC_VPSLLQ:
            break;
        case ZYDIS_MNEMONIC_VPSLLVD:
            break;
        case ZYDIS_MNEMONIC_VPSLLVQ:
            break;
        case ZYDIS_MNEMONIC_VPSLLVW:
            break;
        case ZYDIS_MNEMONIC_VPSLLW:
            break;
        case ZYDIS_MNEMONIC_VPSRAD:
            break;
        case ZYDIS_MNEMONIC_VPSRAQ:
            break;
        case ZYDIS_MNEMONIC_VPSRAVD:
            break;
        case ZYDIS_MNEMONIC_VPSRAVQ:
            break;
        case ZYDIS_MNEMONIC_VPSRAVW:
            break;
        case ZYDIS_MNEMONIC_VPSRAW:
            break;
        case ZYDIS_MNEMONIC_VPSRLD:
            break;
        case ZYDIS_MNEMONIC_VPSRLDQ:
            break;
        case ZYDIS_MNEMONIC_VPSRLQ:
            break;
        case ZYDIS_MNEMONIC_VPSRLVD:
            break;
        case ZYDIS_MNEMONIC_VPSRLVQ:
            break;
        case ZYDIS_MNEMONIC_VPSRLVW:
            break;
        case ZYDIS_MNEMONIC_VPSRLW:
            break;
        case ZYDIS_MNEMONIC_VPSUBB:
            break;
        case ZYDIS_MNEMONIC_VPSUBD:
            break;
        case ZYDIS_MNEMONIC_VPSUBQ:
            break;
        case ZYDIS_MNEMONIC_VPSUBRD:
            break;
        case ZYDIS_MNEMONIC_VPSUBRSETBD:
            break;
        case ZYDIS_MNEMONIC_VPSUBSB:
            break;
        case ZYDIS_MNEMONIC_VPSUBSETBD:
            break;
        case ZYDIS_MNEMONIC_VPSUBSW:
            break;
        case ZYDIS_MNEMONIC_VPSUBUSB:
            break;
        case ZYDIS_MNEMONIC_VPSUBUSW:
            break;
        case ZYDIS_MNEMONIC_VPSUBW:
            break;
        case ZYDIS_MNEMONIC_VPTERNLOGD:
            break;
        case ZYDIS_MNEMONIC_VPTERNLOGQ:
            break;
        case ZYDIS_MNEMONIC_VPTEST:
            break;
        case ZYDIS_MNEMONIC_VPTESTMB:
            break;
        case ZYDIS_MNEMONIC_VPTESTMD:
            break;
        case ZYDIS_MNEMONIC_VPTESTMQ:
            break;
        case ZYDIS_MNEMONIC_VPTESTMW:
            break;
        case ZYDIS_MNEMONIC_VPTESTNMB:
            break;
        case ZYDIS_MNEMONIC_VPTESTNMD:
            break;
        case ZYDIS_MNEMONIC_VPTESTNMQ:
            break;
        case ZYDIS_MNEMONIC_VPTESTNMW:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKHBW:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKHDQ:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKHQDQ:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKHWD:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKLBW:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKLDQ:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKLQDQ:
            break;
        case ZYDIS_MNEMONIC_VPUNPCKLWD:
            break;
        case ZYDIS_MNEMONIC_VPXOR:
            break;
        case ZYDIS_MNEMONIC_VPXORD:
            break;
        case ZYDIS_MNEMONIC_VPXORQ:
            break;
        case ZYDIS_MNEMONIC_VRANGEPD:
            break;
        case ZYDIS_MNEMONIC_VRANGEPS:
            break;
        case ZYDIS_MNEMONIC_VRANGESD:
            break;
        case ZYDIS_MNEMONIC_VRANGESS:
            break;
        case ZYDIS_MNEMONIC_VRCP14PD:
            break;
        case ZYDIS_MNEMONIC_VRCP14PS:
            break;
        case ZYDIS_MNEMONIC_VRCP14SD:
            break;
        case ZYDIS_MNEMONIC_VRCP14SS:
            break;
        case ZYDIS_MNEMONIC_VRCP23PS:
            break;
        case ZYDIS_MNEMONIC_VRCP28PD:
            break;
        case ZYDIS_MNEMONIC_VRCP28PS:
            break;
        case ZYDIS_MNEMONIC_VRCP28SD:
            break;
        case ZYDIS_MNEMONIC_VRCP28SS:
            break;
        case ZYDIS_MNEMONIC_VRCPPS:
            break;
        case ZYDIS_MNEMONIC_VRCPSS:
            break;
        case ZYDIS_MNEMONIC_VREDUCEPD:
            break;
        case ZYDIS_MNEMONIC_VREDUCEPS:
            break;
        case ZYDIS_MNEMONIC_VREDUCESD:
            break;
        case ZYDIS_MNEMONIC_VREDUCESS:
            break;
        case ZYDIS_MNEMONIC_VRNDFXPNTPD:
            break;
        case ZYDIS_MNEMONIC_VRNDFXPNTPS:
            break;
        case ZYDIS_MNEMONIC_VRNDSCALEPD:
            break;
        case ZYDIS_MNEMONIC_VRNDSCALEPS:
            break;
        case ZYDIS_MNEMONIC_VRNDSCALESD:
            break;
        case ZYDIS_MNEMONIC_VRNDSCALESS:
            break;
        case ZYDIS_MNEMONIC_VROUNDPD:
            break;
        case ZYDIS_MNEMONIC_VROUNDPS:
            break;
        case ZYDIS_MNEMONIC_VROUNDSD:
            break;
        case ZYDIS_MNEMONIC_VROUNDSS:
            break;
        case ZYDIS_MNEMONIC_VRSQRT14PD:
            break;
        case ZYDIS_MNEMONIC_VRSQRT14PS:
            break;
        case ZYDIS_MNEMONIC_VRSQRT14SD:
            break;
        case ZYDIS_MNEMONIC_VRSQRT14SS:
            break;
        case ZYDIS_MNEMONIC_VRSQRT23PS:
            break;
        case ZYDIS_MNEMONIC_VRSQRT28PD:
            break;
        case ZYDIS_MNEMONIC_VRSQRT28PS:
            break;
        case ZYDIS_MNEMONIC_VRSQRT28SD:
            break;
        case ZYDIS_MNEMONIC_VRSQRT28SS:
            break;
        case ZYDIS_MNEMONIC_VRSQRTPS:
            break;
        case ZYDIS_MNEMONIC_VRSQRTSS:
            break;
        case ZYDIS_MNEMONIC_VSCALEFPD:
            break;
        case ZYDIS_MNEMONIC_VSCALEFPS:
            break;
        case ZYDIS_MNEMONIC_VSCALEFSD:
            break;
        case ZYDIS_MNEMONIC_VSCALEFSS:
            break;
        case ZYDIS_MNEMONIC_VSCALEPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERDPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERDPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF0DPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF0DPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF0HINTDPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF0HINTDPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF0QPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF0QPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF1DPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF1DPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF1QPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERPF1QPS:
            break;
        case ZYDIS_MNEMONIC_VSCATTERQPD:
            break;
        case ZYDIS_MNEMONIC_VSCATTERQPS:
            break;
        case ZYDIS_MNEMONIC_VSHUFF32X4:
            break;
        case ZYDIS_MNEMONIC_VSHUFF64X2:
            break;
        case ZYDIS_MNEMONIC_VSHUFI32X4:
            break;
        case ZYDIS_MNEMONIC_VSHUFI64X2:
            break;
        case ZYDIS_MNEMONIC_VSHUFPD:
            break;
        case ZYDIS_MNEMONIC_VSHUFPS:
            break;
        case ZYDIS_MNEMONIC_VSQRTPD:
            break;
        case ZYDIS_MNEMONIC_VSQRTPS:
            break;
        case ZYDIS_MNEMONIC_VSQRTSD:
            break;
        case ZYDIS_MNEMONIC_VSQRTSS:
            break;
        case ZYDIS_MNEMONIC_VSTMXCSR:
            break;
        case ZYDIS_MNEMONIC_VSUBPD:
            break;
        case ZYDIS_MNEMONIC_VSUBPS:
            break;
        case ZYDIS_MNEMONIC_VSUBRPD:
            break;
        case ZYDIS_MNEMONIC_VSUBRPS:
            break;
        case ZYDIS_MNEMONIC_VSUBSD:
            break;
        case ZYDIS_MNEMONIC_VSUBSS:
            break;
        case ZYDIS_MNEMONIC_VTESTPD:
            break;
        case ZYDIS_MNEMONIC_VTESTPS:
            break;
        case ZYDIS_MNEMONIC_VUCOMISD:
            break;
        case ZYDIS_MNEMONIC_VUCOMISS:
            break;
        case ZYDIS_MNEMONIC_VUNPCKHPD:
            break;
        case ZYDIS_MNEMONIC_VUNPCKHPS:
            break;
        case ZYDIS_MNEMONIC_VUNPCKLPD:
            break;
        case ZYDIS_MNEMONIC_VUNPCKLPS:
            break;
        case ZYDIS_MNEMONIC_VXORPD:
            break;
        case ZYDIS_MNEMONIC_VXORPS:
            break;
        case ZYDIS_MNEMONIC_VZEROALL:
            break;
        case ZYDIS_MNEMONIC_VZEROUPPER:
            break;
        case ZYDIS_MNEMONIC_WBINVD:
            break;
        case ZYDIS_MNEMONIC_WRFSBASE:
            break;
        case ZYDIS_MNEMONIC_WRGSBASE:
            break;
        case ZYDIS_MNEMONIC_WRMSR:
            break;
        case ZYDIS_MNEMONIC_WRPKRU:
            break;
        case ZYDIS_MNEMONIC_WRSSD:
            break;
        case ZYDIS_MNEMONIC_WRSSQ:
            break;
        case ZYDIS_MNEMONIC_WRUSSD:
            break;
        case ZYDIS_MNEMONIC_WRUSSQ:
            break;
        case ZYDIS_MNEMONIC_XABORT:
            break;
        case ZYDIS_MNEMONIC_XADD:
            break;
        case ZYDIS_MNEMONIC_XBEGIN:
            break;
        case ZYDIS_MNEMONIC_XCHG:
            break;
        case ZYDIS_MNEMONIC_XCRYPT_CBC:
            break;
        case ZYDIS_MNEMONIC_XCRYPT_CFB:
            break;
        case ZYDIS_MNEMONIC_XCRYPT_CTR:
            break;
        case ZYDIS_MNEMONIC_XCRYPT_ECB:
            break;
        case ZYDIS_MNEMONIC_XCRYPT_OFB:
            break;
        case ZYDIS_MNEMONIC_XEND:
            break;
        case ZYDIS_MNEMONIC_XGETBV:
            break;
        case ZYDIS_MNEMONIC_XLAT:
            break;
        case ZYDIS_MNEMONIC_XOR:
            break;
        case ZYDIS_MNEMONIC_XORPD:
            break;
        case ZYDIS_MNEMONIC_XORPS:
            break;
        case ZYDIS_MNEMONIC_XRSTOR:
            break;
        case ZYDIS_MNEMONIC_XRSTOR64:
            break;
        case ZYDIS_MNEMONIC_XRSTORS:
            break;
        case ZYDIS_MNEMONIC_XRSTORS64:
            break;
        case ZYDIS_MNEMONIC_XSAVE:
            break;
        case ZYDIS_MNEMONIC_XSAVE64:
            break;
        case ZYDIS_MNEMONIC_XSAVEC:
            break;
        case ZYDIS_MNEMONIC_XSAVEC64:
            break;
        case ZYDIS_MNEMONIC_XSAVEOPT:
            break;
        case ZYDIS_MNEMONIC_XSAVEOPT64:
            break;
        case ZYDIS_MNEMONIC_XSAVES:
            break;
        case ZYDIS_MNEMONIC_XSAVES64:
            break;
        case ZYDIS_MNEMONIC_XSETBV:
            break;
        case ZYDIS_MNEMONIC_XSHA1:
            break;
        case ZYDIS_MNEMONIC_XSHA256:
            break;
        case ZYDIS_MNEMONIC_XSTORE:
            break;
        case ZYDIS_MNEMONIC_XTEST:
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

