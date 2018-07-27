#include <stdint.h>
#include <elf.h>


const char *phdr_get_type(uint32_t p_type)
{
    switch (p_type) {
        case PT_NULL: return "NULL"; break;
        case PT_LOAD: return "LOAD"; break;
        case PT_DYNAMIC: return "DYNAMIC"; break;
        case PT_INTERP: return "INTERP"; break;
        case PT_NOTE: return "NOTE"; break;
        case PT_SHLIB: return "SHLIB"; break;
        case PT_PHDR: return "PHDR"; break;
        case PT_LOPROC: return "LOPROC"; break;
        case PT_HIPROC: return "HIPROC"; break;
        case PT_GNU_STACK: return "GNU_STACK"; break;
        default: return ""; break;
    };
}


const char *phdr_get_flags(uint32_t p_flags)
{
    switch (p_flags) {
        case PF_X: return "X"; break;
        case PF_W: return "W"; break;
        case PF_R: return "R"; break;
        case PF_X | PF_W: return "XW"; break;
        case PF_W | PF_R: return "RW"; break;
        case PF_X | PF_W | PF_R: return "XWR"; break;
        default: return "R E"; break; // wrong: check for correct flags
    }
}

