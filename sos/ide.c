#include "ide.h"
#include "x86.h"

void wait_disk(void) {
    while((inb(IDE_PORT(IDE_CHANNEL_1, LBA_RW_ST)) & 0xc0) != 0x40) { }
}

void read_sect(void *dst, unsigned int offset) {
    wait_disk();

    outb(IDE_PORT(IDE_CHANNEL_1, LBA_SECTOR_COUNT), 1);
    outb(IDE_PORT(IDE_CHANNEL_1, LBA_OFFSET_0_7), offset);
    outb(IDE_PORT(IDE_CHANNEL_1, LBA_OFFSET_8_15), offset >> 8);
    outb(IDE_PORT(IDE_CHANNEL_1, LBA_OFFSET_16_23), offset >> 16);
    outb(IDE_PORT(IDE_CHANNEL_1, LBA_MASTER_SLAVE_24_27), (offset >> 24) | 0xe0);
    outb(IDE_PORT(IDE_CHANNEL_1, LBA_RW_ST), 0x20);

    wait_disk();
    insl(IDE_PORT(IDE_CHANNEL_1, LBA_RW_LOOP), dst, 512/4);    
}
