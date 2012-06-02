#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#define DEV_NUM 1
#define DEV_NAME "char_sample"

MODULE_LICENSE("GPLv2");

struct char_sample_dev {
	dev_t dev;
	struct cdev cdev;
} sdev;

static int char_sample_open(struct inode *inode, struct file *filp) {
	printk(KERN_ALERT "char sample open %p.\n", filp);
	return 0;
}

static ssize_t char_sample_write(struct file *filp, const char __user *addr, size_t size, loff_t *offp) {
	printk(KERN_ALERT "char sample write.\n");

	char *mem = (char *)kmalloc(size + 1, GFP_KERNEL);

	if (mem == NULL) {
		return -1;
	}

	memset(mem, 0, size + 1);

	int ret = copy_from_user(mem, addr, size);

	if (ret) {
		printk(KERN_ALERT "copy from user error %d.\n", ret);
		kfree(mem);
		return -1;
	}

	printk(KERN_ALERT "write: %s\n", mem);
	kfree(mem);

	return size;
}

#define STR "read from char sample read\n"

static ssize_t char_sample_read(struct file *filp, char __user *addr, size_t size, loff_t *offp) {
	printk(KERN_ALERT "char sample read %d.\n", size);
	int ret = copy_to_user(addr, STR, sizeof(STR)); 

	if (ret) {
		printk(KERN_ALERT "copy to user error.\n");
		return -1;
	}
	
	return sizeof(STR);
}

static struct file_operations char_sample_fops = {
	.open = char_sample_open,
	.write = char_sample_write,
	.read = char_sample_read	
};

static int __init char_sample_init(void) {
	printk(KERN_ALERT "char sample init.\n");

	int ret = alloc_chrdev_region(&(sdev.dev), 0, DEV_NUM, DEV_NAME);

	if (ret < 0) {
		printk(KERN_ALERT "can not alloc char device number.\n");
		return ret;
	}

	cdev_init(&(sdev.cdev), &char_sample_fops);
	ret = cdev_add(&(sdev.cdev), sdev.dev, DEV_NUM);

	if (ret < 0) {
		printk(KERN_ALERT "can not add char device.\n");
		unregister_chrdev_region(sdev.dev, DEV_NUM);
		return ret;
	}

	return 0;
}

static void __exit char_sample_exit(void) {
	printk(KERN_ALERT "char sample exit.\n");
	cdev_del(&(sdev.cdev));
	unregister_chrdev_region(sdev.dev, DEV_NUM);
}

module_init(char_sample_init);
module_exit(char_sample_exit);
