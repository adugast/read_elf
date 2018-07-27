#include <stdio.h>
#include <stdlib.h>

#include "read_elf.h"



elf_file_t *re_create_handle(const char *pathname)
{
    elf_file_t *ret = NULL;

    elf_file_t *hdl = calloc(1, sizeof(elf_file_t));
    if (hdl == NULL)
        return NULL;

    hdl->file = fopen(pathname, "rb");
    if (hdl->file == NULL)
        goto clean_hdl;

    // retrieve elf file header
    hdl->ehdr64 = calloc(1, sizeof(Elf64_Ehdr));
    if (hdl->ehdr64 == NULL)
        goto clean_hdl_file;

    fread(hdl->ehdr64, 1, sizeof(Elf64_Ehdr), hdl->file);

    if (hdl->ehdr64->e_ident[EI_MAG0] != ELFMAG0 &&
            hdl->ehdr64->e_ident[EI_MAG1] != ELFMAG1 &&
            hdl->ehdr64->e_ident[EI_MAG2] != ELFMAG2 &&
            hdl->ehdr64->e_ident[EI_MAG3] != ELFMAG3)
        goto clean_hdl_file_ehdr;

    // retrieve program header
    hdl->phdr64 = calloc(1, hdl->ehdr64->e_phentsize * hdl->ehdr64->e_phnum);
    if (hdl->phdr64 == NULL)
        goto clean_hdl_file_ehdr_phdr;

    fseek(hdl->file, hdl->ehdr64->e_phoff, SEEK_SET);
    fread(hdl->phdr64, 1, hdl->ehdr64->e_phentsize * hdl->ehdr64->e_phnum, hdl->file);

    // retrieve section header
//    hdl->shdr64 = calloc(1, sizeof(Elf64_Shdr));
    hdl->shdr64 = calloc(1, hdl->ehdr64->e_shentsize * hdl->ehdr64->e_shnum);
    if (hdl->shdr64 == NULL)
        goto clean_hdl_file_ehdr_phdr_shdr;

    fseek(hdl->file, hdl->ehdr64->e_shoff, SEEK_SET);
//    fread(hdl->shdr64, 1, sizeof(Elf64_Shdr), hdl->file);
    fread(hdl->shdr64, 1, hdl->ehdr64->e_shentsize * hdl->ehdr64->e_shnum, hdl->file);

    // if everything succeed, return the new handle
    ret = hdl;
    goto success;

clean_hdl_file_ehdr_phdr_shdr:
    free(hdl->shdr64);
clean_hdl_file_ehdr_phdr:
    free(hdl->phdr64);
clean_hdl_file_ehdr:
    free(hdl->ehdr64);
clean_hdl_file:
    fclose(hdl->file);
clean_hdl:
    free(hdl);
success:
    return ret;
}


Elf64_Ehdr *re_get_elf_header(elf_file_t *hdl)
{
    return hdl->ehdr64;
}


Elf64_Phdr *re_get_program_header(elf_file_t *hdl)
{
    return hdl->phdr64;
}


Elf64_Shdr *re_get_section_header(elf_file_t *hdl)
{
    return hdl->shdr64;
}


void re_free_handle(elf_file_t *hdl)
{
    fclose(hdl->file);
    free(hdl->shdr64);
    free(hdl->phdr64);
    free(hdl->ehdr64);
    free(hdl);
}

