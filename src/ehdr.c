#include <stdint.h>
#include <elf.h>


const char *ehdr_get_class(unsigned char e_class)
{
    switch (e_class) {
        case ELFCLASSNONE: return "This class is invalid"; break;
        case ELFCLASS32: return "ELF32"; break;
        case ELFCLASS64: return "ELF64"; break;
        default: return ""; break;
    }
}


const char *ehdr_get_data(unsigned char e_data)
{
    switch (e_data) {
        case ELFDATANONE: return "Unknown data format"; break;
        case ELFDATA2LSB: return "2's complement, little-endian"; break;
        case ELFDATA2MSB: return "2's complement, big-endian"; break;
        default: return ""; break;
    }
}


const char *ehdr_get_version(unsigned char e_version)
{
    switch (e_version) {
        case EV_NONE: return "(Invalid version)"; break;
        case EV_CURRENT: return "(Current version)"; break;
        default: return ""; break;
    }
}


const char *ehdr_get_osabi(unsigned char e_osabi)
{
    switch (e_osabi) {
        case ELFOSABI_SYSV: return "UNIX System V ABI"; break;
        case ELFOSABI_HPUX: return "HP-UX ABI"; break;
        case ELFOSABI_NETBSD: return "NetBSD ABI"; break;
        case ELFOSABI_LINUX: return "Linux ABI"; break;
        case ELFOSABI_SOLARIS: return "Solaris ABI"; break;
        case ELFOSABI_IRIX: return "IRIX ABI"; break;
        case ELFOSABI_FREEBSD: return "FreeBSD ABI"; break;
        case ELFOSABI_TRU64: return "TRU64 UNIX ABI"; break;
        case ELFOSABI_ARM: return "ARM architecture ABI"; break;
        case ELFOSABI_STANDALONE: return "Stand-alone (embedded) ABI"; break;
        default: return ""; break;
    }
}


const char *ehdr_get_type(unsigned char e_type)
{
    switch (e_type) {
        case ET_NONE: return "NONE (Unknown type)"; break;
        case ET_REL: return "REL (Relocatable file)"; break;
        case ET_EXEC: return "EXEC (Executable file)"; break;
        case ET_DYN: return "DYN (Shared file)"; break;
        case ET_CORE: return "CORE (Core file)"; break;
        default: return ""; break;
    }
}


const char *ehdr_get_machine(unsigned char e_machine)
{
    switch (e_machine) {
        case EM_NONE: return "An unknown machine"; break;
        case EM_M32: return "AT&T WE 32100"; break;
        case EM_SPARC: return "Sun Microsystems SPARC"; break;
        case EM_386: return "Intel 80386"; break;
        case EM_68K: return "Motorola 68000"; break;
        case EM_88K: return "Motorola 88000"; break;
        case EM_860: return "Intel 80860"; break;
        case EM_MIPS: return "MIPS RS3000 (big-endian only)"; break;
        case EM_PARISC: return "HP/PA"; break;
        case EM_SPARC32PLUS: return "SPARC with enhanced instruction set"; break;
        case EM_PPC: return "PowerPC"; break;
        case EM_PPC64: return "PowerPC 64-bit"; break;
        case EM_S390: return "IBM S/390"; break;
        case EM_ARM: return "Advanced RISC Machines"; break;
        case EM_SH: return "Renesas SuperH"; break;
        case EM_SPARCV9: return "SPARC v9 64-bit"; break;
        case EM_IA_64: return "Intel Itanium"; break;
        case EM_X86_64: return "AMD x86-64"; break;
        case EM_VAX: return "DEC Vax"; break;
        default: return ""; break;
    }
}

