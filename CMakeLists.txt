#########
# CMAKE #
#########

cmake_minimum_required(VERSION 2.6.2)

project(read_elf)

## set compilation flags
set(CMAKE_C_FLAGS "-W -Wall -pedantic -std=c99 -std=gnu99 -g")

## set the target name and source
add_executable(
    read_elf
    src/main.c
    src/read_elf.c
    src/argument_manager.c
    src/ehdr.c
    src/phdr.c
    src/shdr.c
)

