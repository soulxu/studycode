#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("soulxu");

#define MIN_NUM 1

dev_t dev;

struct scull_data {
	char name[100];
	dev_t mdev;
};


struct scull_data sculls = {
	.name = "aaa",
	.mdev = NULL,
};

int scull_open(struct inode *, struct file *);

struct file_operations scull_fops = {
	.owner	= THIS_MODULE,
	.open	= scull_open,
};



struct cdev *scull_cdev = NULL;


int scull_open(struct inode *node, struct file *fp) {
	printk(KERN_ALERT"exec scull_open the devices is %d : %d\n", imajor(node), iminor(node));
	struct scull_data *d = container_of(node->i_cdev, struct scull_data, mdev);
	printk(KERN_ALERT"data : %p\n", d);
	
	return 0;	
}

static int __init scull_init(void) {
	int result = 0;

	result = alloc_chrdev_region(&dev, 0, 1, "scull");
	
	if (result < 0) {
		printk(KERN_ALERT"scull: can't get major\n");
		return result;
	}

	printk(KERN_ALERT"scull: get major number is %d : %d\n", MAJOR(dev), MINOR(dev));
	scull_cdev = cdev_alloc();
	printk(KERN_ALERT"scull: alloc cdev\n");
	cdev_init(scull_cdev, &scull_fops);
	scull_cdev->owner = THIS_MODULE;
	
	result = cdev_add(scull_cdev, dev, 1);

	sculls.mdev = scull_cdev;
	printk(KERN_ALERT"sculls addr : %p", &sculls);
	if (result < 0) {
		printk(KERN_ALERT"scull: cdev_add error");
	}

	return 0;
}

static void __exit scull_cleanup(void) {
	cdev_del(scull_cdev);
	printk(KERN_ALERT"clean cdev\n");
	unregister_chrdev_region(dev, MIN_NUM);
	printk(KERN_ALERT"clean dev number\n");
}

module_init(scull_init);
module_exit(scull_cleanup);
