#include <stdio.h>

#include "argument_manager.h"
#include "read_elf.h"
#include "ehdr.h"
#include "phdr.h"
#include "shdr.h"


/* Display the ELF file header */
static void dump_elf_file_header(Elf64_Ehdr *ehdr)
{
    printf("ELF HEADER:\n");
    printf("  Magic:   ");
    unsigned int i;
    for (i = 0; i < EI_NIDENT; i++)
        printf("%02x ", ehdr->e_ident[i]);
    printf("\n");
    printf("  %-35s%s\n", "Class:", ehdr_get_class(ehdr->e_ident[EI_CLASS]));
    printf("  %-35s%s\n", "Data:", ehdr_get_data(ehdr->e_ident[EI_DATA]));
    printf("  %-35s%d %s\n", "Version:", ehdr->e_ident[EI_VERSION], ehdr_get_version(ehdr->e_ident[EI_VERSION]));
    printf("  %-35s%s\n", "OS/ABI:", ehdr_get_osabi(ehdr->e_ident[EI_OSABI]));
    printf("  %-35s%d\n", "ABI Version:", ehdr->e_ident[EI_ABIVERSION]);
    printf("  %-35s%s\n", "Type:", ehdr_get_type(ehdr->e_type));
    printf("  %-35s%s\n", "Machine:", ehdr_get_machine(ehdr->e_machine));
    printf("  %-35s%s%d\n", "Version:", "0x", ehdr->e_version);
    printf("  %-35s%s%lx\n", "Entry point address:", "0x", ehdr->e_entry);
    printf("  %-35s%ld %s\n", "Start of program headers:", ehdr->e_phoff, "(bytes into file)");
    printf("  %-35s%ld %s\n", "Start of section headers:", ehdr->e_shoff, "(bytes into file)");
    printf("  %-35s%s%x\n", "Flags:", "0x", ehdr->e_flags);
    printf("  %-35s%d %s\n", "Size of this header:", ehdr->e_ehsize, "(bytes)");
    printf("  %-35s%d %s\n", "Size of program headers:", ehdr->e_phentsize, "(bytes)");
    printf("  %-35s%d\n", "Number of program headers:", ehdr->e_phnum);
    printf("  %-35s%d %s\n","Size of section headers:", ehdr->e_shentsize, "(bytes)");
    printf("  %-35s%d\n", "Number of section headers:", ehdr->e_shnum);
    printf("  %-35s%d\n", "Section header string table index:", ehdr->e_shstrndx);
}


/* Display the program header */
static void dump_program_header(Elf64_Ehdr *ehdr, Elf64_Phdr *phdr)
{
    printf("\nElf file type is %s\n", ehdr_get_type(ehdr->e_type));
    printf("Entry point 0x%lx\n", ehdr->e_entry);
    printf("There are %d program headers, starting at offset %ld\n", ehdr->e_phnum, phdr->p_offset);
    printf("\nProgram Headers:\n");
    printf("  %-15s%-19s%-19s%-19s\n", "Type", "Offset", "VirtAddr", "PhysAddr");
    printf("%*c%-19s%-19s%s\n", 17, ' ', "FileSiz", "MemSiz", "Flags Align");
    unsigned int i;
    for (i = 0; i < ehdr->e_phnum; i++) {
        printf("  %-15s0x%016lx 0x%016lx 0x%016lx\n",
                phdr_get_type(phdr[i].p_type), phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr);
        printf("%*c%s%016lx 0x%016lx  %-5s  %lx\n", 17, ' ',
                "0x", phdr[i].p_filesz, phdr[i].p_memsz, phdr_get_flags(phdr[i].p_flags), phdr[i].p_align);
    }
    printf("\n Section to Segment mapping:\n");
    printf("  Segment Sections...\n");
}


const char *key_to_flags = "Key to Flags:\n"
"  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n"
"  L (link order), O (extra OS processing required), G (group), T (TLS),\n"
"  C (compressed), x (unknown), o (OS specific), E (exclude),\n"
"  l (large), p (processor specific)\n";


/* Display the section header */
static void dump_section_header(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    printf("There are %d section headers, starting at offset 0x%lx:\n\n", ehdr->e_shnum, ehdr->e_shoff);
    printf("Section Headers:\n");
    printf("  %-23s%-17s%-18s%s\n", "[Nr] Name", "Type", "Address", "Offset");
    printf("       %-18s%-17s%s\n", "Size", "EntSize", "Flags  Link  Info  Align");

    unsigned int i;
    for (i = 0; i < ehdr->e_shnum; i++) {
        const Elf64_Shdr *ite = &shdr[i];

        printf("  [%*d] %-16s  %-16s %016lx  %08lx\n",
                2, i, "section_name", shdr_get_type(ite->sh_type), ite->sh_addr, ite->sh_offset);
        printf("       %016lx  %016lx  %-9s%-6d%-6d%ld\n",
                ite->sh_size, ite->sh_entsize, shdr_get_flags(ite->sh_flags), ite->sh_link, ite->sh_info, ite->sh_addralign);
    }
    printf("%s", key_to_flags);
}


static int read_elf(struct argument *args)
{
    elf_file_t *hdl = re_create_handle(args->file);
    if (hdl == NULL)
        return -1;

    /* retreive pointers for each elf file sections */
    Elf64_Ehdr *ehdr = re_get_elf_header(hdl);
    Elf64_Phdr *phdr = re_get_program_header(hdl);
    Elf64_Shdr *shdr = re_get_section_header(hdl);

    if (args->ehdr_flag)
        dump_elf_file_header(ehdr);

    if (args->phdr_flag)
        dump_program_header(ehdr, phdr);

    if (args->shdr_flag)
        dump_section_header(ehdr, shdr);

    re_free_handle(hdl);

    return 0;
}


int main(int argc, char *argv[])
{
    struct argument args;

    argument_manager(argc, argv, &args);

    read_elf(&args);

    return 0;
}

