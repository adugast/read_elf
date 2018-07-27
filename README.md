# read_elf [![Language: C](https://img.shields.io/badge/Language-C-brightgreen.svg)](https://en.wikipedia.org/wiki/C_(programming_language)) [![Builder: CMake](https://img.shields.io/badge/Builder-CMake-brightgreen.svg)](https://cmake.org/)  [![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)   

Own implementation of the readelf tool. (Displays information about ELF files: .axf, .bin, .elf, .o, .prx, .puff, .ko, .mod and .so)

## Usage:

```
Usage: ./read_elf [params] <elf-file>   
Available params:    
 -a, --all              : Equivalent to: -h -l -S   
 -h, --file-header      : Display the ELF file header   
 -l, --program-headers: : Display the program headers   
 -S, --section-headers  : Display the sections headers  
 -H, --help             : Display this help and exit  
 -v, --version          : Show version information    
```

## Output:

```
$>./read_elf -h read_elf    
ELF HEADER:    
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00  
  Class:                             ELF64   
  Data:                              2's complement, little-endian  
  Version:                           1 (Current version)
  OS/ABI:                            UNIX System V ABI
  ABI Version:                       0
  Type:                              DYN (Shared file)
  Machine:                           AMD x86-64
  Version:                           0x1
  Entry point address:               0xef0
  Start of program headers:          64 (bytes into file)
  Start of section headers:          32904 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         36
  Section header string table index: 35
```

## More info:

* [man (5) elf](https://www.freebsd.org/cgi/man.cgi?query=elf&sektion=5&apropos=0&manpath=FreeBSD+7.0-RELEASE) - format of ELF executable binary files
* [ELF Format](http://www.skyfree.org/linux/references/ELF_Format.pdf) - Executable and Linkable Format

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
