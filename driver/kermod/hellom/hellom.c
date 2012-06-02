#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xu Hejie");
MODULE_DESCRIPTION("Xu Hejie write HelloWorld");

static char *whom = "world";
static int howmany = 1;

module_param(whom, charp, S_IRUGO);
module_param(howmany, int, S_IRUGO);


static int __init hello_init(void) {
	int i = 0;

	printk(KERN_ALERT"the kernel version is "UTS_RELEASE"\n");

	for (i = 0; i < howmany; i++) {
		printk(KERN_ALERT"Hello %s\n", whom);
	}

	printk(KERN_ALERT"current process id is %d and command is %s\n", current->pid, current->comm);
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_ALERT"Bye Bye %s\n", whom);
}

module_init(hello_init);
module_exit(hello_cleanup);
