#include <stdio.h>

#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <memory.h>
#include <stdlib.h>

/*
uint get_pixel(uint red, uint green, uint blue, uint alpha) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}
*/

ushort get_pixel(uint red, uint green, uint blue, uint alpha) {
    red <<= 11;
    green <<= 5;
    return red | green | blue;
}

void draw_rect(int x, int y, int width, int height, int line_size, char *mem, ushort color, int pixel_size) {
    int i = 0;
    int j = 0;
    char *p = NULL;

    for (i = 0; i < height; i++) {
        p = mem + (y + i) * line_size;
        //printf("draw line : %d :: %x\n", i, p);

        p += x * pixel_size / 8;
        for (j = 0; j < width; j++) {
            memset(p, color, pixel_size / 8);
            p+=(pixel_size / 8);
        }
    }
}

int main(int argc, char **argv) {

    if (argc < 9) {
        exit(-1);
    }

    int fb_dev = open(argv[1], O_RDWR);
    
    if (fb_dev < 0) {
        perror("can not fb0.");
        return -1;
    }

    struct fb_var_screeninfo var_info;

    if (ioctl(fb_dev, FBIOGET_VSCREENINFO, &var_info) < 0) {
        return -3;
    }


    int line_size = var_info.xres * var_info.bits_per_pixel / 8;
    int buffer_size = line_size * var_info.yres;
    printf("line_size: %d\n", line_size);
    printf("buffer size: %d\n", buffer_size);

    //var_info.xoffset = 0;
    //var_info.yoffset = 0;
    //var_info.bits_per_pixel = 32;
    
    //ioctl(fb_dev, FBIOPUT_VSCREENINFO, &var_info);

    int *screen_mem = (int *)mmap(NULL, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb_dev, 0);

    if (screen_mem <= 0) {
        perror("can not mmap fb");
        return -2;
    }

    int rect_x = atoi(argv[2]);
    int rect_y = atoi(argv[3]);
    int rect_width = atoi(argv[4]);
    int rect_height = atoi(argv[5]);

    draw_rect(rect_x, rect_y, rect_width, rect_height, line_size, (char *)screen_mem, get_pixel(atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), 0xff), var_info.bits_per_pixel);


/*
    int i = 0;
    int j = 0;

    for (i = 0; i < rect_height; i++) {
        
        for (j = 0; j < rect_width; j++) {

        }
    }
    int i = 0;
    for (i = 0; i < buffer_size / 4; i++) {
        //printf("write\n");
        *(screen_mem + i) = get_pixel(0x0, 0xff, 0, 0xff);
    }
*/
    printf("xres: %d\n", var_info.xres);
    printf("yres: %d\n", var_info.yres);
    printf("bits per pixel: %d\n", var_info.bits_per_pixel);
    printf("red length: %d, %d\n", var_info.red.offset, var_info.red.length);
    printf("green length: %d, %d\n", var_info.green.offset, var_info.green.length);
    printf("blue length: %d, %d\n", var_info.blue.offset, var_info.blue.length);
    printf("trans length: %d, %d\n", var_info.transp.offset, var_info.transp.length);

    //memset(screen_mem, 0, buffer_size);
    close(fb_dev);

    return 0;
}
