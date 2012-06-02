#ifndef _IDE_H_
#define _IDE_H_

// IDE Channel number
#define IDE_CHANNEL_1 0
#define IDE_CHANNEL_2 1

#define IDE_PORT(channel, port) \
    channel ? 0x170 + port : 0x1F0 + port

//CHS mode
#define CHS_RW_LOOP                          0 //每次读取1个word,反复循环，直到读完所有数据
#define CHS_SECTOR_COUNT                2  //要读的扇区数
#define CHS_SECTOR_NUMBER             3 //扇区号
#define CHS_CYLINDER_LOW_8             4 //柱面的低8位
#define CHS_CYLINDER_HIGH_8            5 // 柱面的高8位
#define CHS_MASTER_SLAVE_HEADER   6 //7~5位,101,第4位0表示主盘,1表示从盘,3~0位,磁头号
#define CHS_RW_ST                                7 //0x20为读, 0x30为写, 第4位为0表示读写完成，否则要一直循环等待

//LBA mode
#define LBA_RW_LOOP                      0
#define LBA_SECTOR_COUNT            2
#define LBA_OFFSET_0_7                                  3
#define LBA_OFFSET_8_15                                4
#define LBA_OFFSET_16_23                              5
#define LBA_MASTER_SLAVE_24_27   6
#define LBA_RW_ST                            7

void wait_disk(void);
void read_sect(void *dst, unsigned int offset);

#endif
