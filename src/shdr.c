#include <stdint.h>
#include <elf.h>


const char *shdr_get_type(uint32_t sh_type)
{
    switch (sh_type) {
        case SHT_NULL: return "NULL"; break;
        case SHT_PROGBITS: return "PROGBITS"; break;
        case SHT_SYMTAB: return "SYMTAB"; break;
        case SHT_STRTAB: return "STRTAB"; break;
        case SHT_RELA: return "RELA"; break;
        case SHT_HASH: return "HASH"; break;
        case SHT_DYNAMIC: return "DYNAMIC"; break;
        case SHT_NOTE: return "NOTE"; break;
        default: return ""; break;
    }
}


const char *shdr_get_flags(uint32_t sh_flags)
{
    switch (sh_flags) {
        case SHF_WRITE: return "W"; break;
        case SHF_ALLOC: return "A"; break;
        case SHF_EXECINSTR: return "X"; break;
        case SHF_MASKPROC: return "M"; break;
        default: return ""; break;
    }

}

