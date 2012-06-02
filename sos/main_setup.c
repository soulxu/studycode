#include "ide.h"
#include "elf.h"
#include "util.h"

void main_setup() {
    char *info = "Loading kernel...";
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)0x102000;
    char *p = (char *)ehdr;
    int i = 0;
    int j = 0;

    print_str(info, 'A');
    /*
    boot.o+setup.o == 512b at sector 0(MBR)
    main_setup.o == 4096b at sector 1-8(8)
    main.exec at sector 9+
    read main.exec's first sector
    */
    read_sect(p, 9);
    
    Elf32_Shdr *shdr = (Elf32_Shdr *) ((char *)ehdr + ehdr->e_shoff);
    Elf32_Phdr *phdr = (Elf32_Phdr *)((char *)ehdr + ehdr->e_phoff);

    void (*main)();
    
    for (i = 0; i < ehdr->e_phnum; i++) {
        if ((phdr + i)->p_type == PT_LOAD) {
            p = (char *)((phdr + i)->p_vaddr - (phdr + i)->p_offset);
            for (j = 0; j < (phdr + i)->p_filesz/512; j++) {
                read_sect(p, 9+j);
                p += 512;
            }
            
            if (((phdr + i)->p_filesz%512) > 0) {
                read_sect(p, 9+j);
            }

            break;
        }
    }

    main = (void (*)())ehdr->e_entry;    
    main();
}
