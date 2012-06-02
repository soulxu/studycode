#include <linux/module.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/jiffies.h>
#include <linux/time.h>

MODULE_LICENSE("GPLv2");

#define GPIOK_START 0x7f008800
#define GPIOKCON0 0x7f008800
#define GPIOKDAT  0x7f008808

#define LED0_CON 0x7f008802

struct resource *res = NULL;
int *gpiok_mem = NULL;

#define GPIO_INPUT      0x0
#define GPIO_OUTPUT     0x1

#define GPIO_CON_BIT_NUM 4

//取n开始的4位数值
#define GPIO_CON_VAL(base, n) ((base & (0xF << (n * GPIO_CON_BIT_NUM))) >> (n * GPIO_CON_BIT_NUM))

static int direction = 0;

void set_gpio_con(void *base, int gpio_num, int val) {
        if (base == NULL) {
                printk(KERN_ALERT "base is null.\n");
                return;
        }

        if (gpio_num > 8) {
                printk(KERN_ALERT "one con only has 8 gpio.\n");
                return;
        }

        int o = ioread32(base);
        int r = 0;
        int i = 0;
        printk(KERN_ALERT "set_gpio_con: orig val : %x", o);

        for (i = 7; i >= 0; i--) {
                if (gpio_num == i) 
                        r |= val << (gpio_num * GPIO_CON_BIT_NUM);  
                else {
                        printk(KERN_ALERT "set_gpio_con: %d, %x", i, GPIO_CON_VAL(o, i));
                        r |= GPIO_CON_VAL(o, i) << (i * GPIO_CON_BIT_NUM);
                }
        }

        printk(KERN_ALERT "set_gpio_con: %x", r);
        iowrite32(r, base);
}

void set_gpio(void *base, int gpio_num, int is_on) {
        if (base == NULL) {
                printk(KERN_ALERT "base is null.\n");
                return;
        }

        if (gpio_num > 16) {
                printk(KERN_ALERT "on gio dat only has 16 gpio\n");
                return;
        }

        uint16_t r = ioread16(base);
        //printk(KERN_ALERT "set_gpio: orig val: %x", r);

        if (is_on) 
                r = r & (0xffff ^ (0x1 << gpio_num));
        else
                r = r | (0x1 << gpio_num);

        //printk(KERN_ALERT"set_gpio: %x", r);
        iowrite16(r, base);
}

static int led_num = 0;

void timer_func(unsigned long data) {
        struct timer_list *t = (struct timer_list *)data;
        t->expires = jiffies + 50;
/*      只能1-3左右循环*/
        led_num = ((led_num  + 1) % 5) ? led_num : led_num * -1;
        int next = led_num + 1;

        set_gpio(gpiok_mem + 2, abs(led_num) + 3, 0);         
        set_gpio(gpiok_mem + 2, abs(next) + 3, 1);         

/*
        int next = (led_num + 1) % 4;

        if (!next) {
                direction = ~direction;
                next = (next + 1) % 4;
        }

        if (direction) {
                set_gpio(gpiok_mem + 2, abs(led_num) + 4, 0);         
                set_gpio(gpiok_mem + 2, abs(next) + 4, 1);         
        }
        else {
                set_gpio(gpiok_mem + 2, 7 - abs(led_num), 0);         
                set_gpio(gpiok_mem + 2, 7 - abs(next), 1);         
        }
*/
        led_num = next;
        add_timer(t);
}

static struct timer_list timer;

static int __init gpio_led_init(void) {
        res = request_mem_region(GPIOK_START, 12, "GPIOK");

        if (res == NULL) {
                printk(KERN_ALERT "can not request memory region.\n");
                return -1;
        }

        gpiok_mem = ioremap(GPIOK_START, 12);
        
        if (gpiok_mem == NULL) {
                printk("can not remap io memory.\n");
                return -2;
        }

        set_gpio_con(gpiok_mem, 4, GPIO_OUTPUT);
        set_gpio_con(gpiok_mem, 5, GPIO_OUTPUT);
        set_gpio_con(gpiok_mem, 6, GPIO_OUTPUT);
        set_gpio_con(gpiok_mem, 7, GPIO_OUTPUT);


        init_timer(&timer);
        timer.function = timer_func;
        timer.expires = jiffies + 100;
        timer.data = (unsigned long)&timer;
        add_timer(&timer);

        return 0;
}

static void __exit gpio_led_cleanup(void) {
        set_gpio(gpiok_mem + 2, 4, 0);         
        set_gpio(gpiok_mem + 2, 5, 0);         
        set_gpio(gpiok_mem + 2, 6, 0);         
        set_gpio(gpiok_mem + 2, 7, 0);         

        del_timer_sync(&timer);
        iounmap(gpiok_mem);
        release_mem_region(GPIOK_START, 12);
}

module_init(gpio_led_init);
module_exit(gpio_led_cleanup);
