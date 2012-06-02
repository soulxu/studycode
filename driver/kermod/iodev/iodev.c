#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/ioport.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xuhejie");
MODULE_DESCRIPTION("IO study module");

#define DEV_NUM 1
#define DEV_NAME "iodev"

dev_t iodev_num;

int add_iodev;

static unsigned long base = 0x61;

struct iodev_data {
    struct cdev mdev;
    struct resource *res;
};

struct iodev_data iodev;

int iodev_open(struct inode *, struct file *);
int iodev_release(struct inode *, struct file *);
ssize_t iodev_read(struct file *, char __user *, size_t, loff_t *);
ssize_t iodev_write(struct file *, const char __user *, size_t, loff_t *);

struct file_operations iodev_ops = {
    .owner      = THIS_MODULE,
    .open       = iodev_open,
    .release    = iodev_release,
    .read       = iodev_read,
    .write      = iodev_write,
};

int iodev_open(struct inode *inode, struct file *filp) {
    
    return 0;
}

int iodev_release(struct inode *inode, struct file *filp) {
    return 0;
}

ssize_t iodev_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
    unsigned int chr = inb(base);
    printk(KERN_ALERT"mcdev: %d", chr);
    return 1;
}

ssize_t iodev_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
    outb(0xAA, base);
    printk(KERN_ALERT"mcdev: write");
    return 1;
}

static int __init iodev_init(void) {
    int ret = 0;
    dev_t dev_num;

    ret = alloc_chrdev_region(&iodev_num, 0, DEV_NUM, DEV_NAME);
    
    if(ret < 0) {
        printk(KERN_ALERT"can not alloc num");
        return ret;
    }
    
    dev_num = MKDEV(MAJOR(iodev_num), 0);
    cdev_init(&(iodev.mdev), &iodev_ops); 
    iodev.mdev.owner = THIS_MODULE;
    ret = cdev_add(&(iodev.mdev), dev_num, 1);
    printk(KERN_ALERT"create dev");
    if (ret < 0) {
        return ret;
    }   
    
    iodev.res = request_region(base, 2, DEV_NAME);
    if (iodev.res == NULL) {
        printk(KERN_ALERT"request resource failed\n");
        cdev_del(&(iodev.mdev));
        unregister_chrdev_region(iodev_num, DEV_NUM);
        return -1;
    }
    
    return 0;
}

static void __exit iodev_cleanup(void) {
    release_region(base, 2);
    cdev_del(&(iodev.mdev));
    unregister_chrdev_region(iodev_num, DEV_NUM);
}

module_init(iodev_init);
module_exit(iodev_cleanup);


