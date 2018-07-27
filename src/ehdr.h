#ifndef __EHDR_H__
#define __EHDR_H__


const char *ehdr_get_class(unsigned char e_class);
const char *ehdr_get_data(unsigned char e_data);
const char *ehdr_get_version(unsigned char e_version);
const char *ehdr_get_osabi(unsigned char e_osabi);
const char *ehdr_get_type(unsigned char e_type);
const char *ehdr_get_machine(unsigned char e_machine);


#endif /* __EHDR_H__ */

