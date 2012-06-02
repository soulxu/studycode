#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("soulxu");

static int many = 1;
module_param(many, int, S_IRUGO);

static int hello_init(void) {
	int i;
	for (i = 0; i < many; i++) {
		printk(KERN_ALERT" Hello world\n");
	}
	return 0;
}

static void hello_exit(void) {
	printk(KERN_ALERT"Goodbye world\n");
}

module_init(hello_init);
module_exit(hello_exit);

