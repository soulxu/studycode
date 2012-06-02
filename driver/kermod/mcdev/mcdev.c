#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/wait.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xuhejie");
MODULE_DESCRIPTION("Xuhejie's study module");

#define DEV_NUM 2
#define DEV_NAME "mcdev"
#define INIT_DATA "mcdev"

#define MCDEV_IOC_MAGIC 'k'
#define MCDEV_IOCSETBUF _IOW(MCDEV_IOC_MAGIC, 1, char *)

#ifdef MCDEV_DEBUG
	#define PDEBUG(fmt, args...) printk(KERN_ALERT"mcdev: "fmt, ## args)
#else
	#define PDEBUG(fmt, args...)
#endif // end MCDEV_DEBUG

dev_t mcdev_num;

struct mcdev_data {
	char *buf;
	int buf_size;
	struct cdev mdev;
	struct semaphore sem;
	wait_queue_head_t wait_queue;
};

struct mcdev_data mcdevs[DEV_NUM] = {
	{
	.buf 		= NULL,
	.buf_size 	= 0,
	.mdev 		= {0}
	},
	{
	.buf		= NULL,
	.buf_size	= 0,
	.mdev		= {0}
	}
};

/*
 * proc

int mcdev_proc_read(char *page, char **start, off_t offset, int count, int *eof, void *data) {
	//(*start)++;
	PDEBUG("mcdev_proc_read\n");
	//PDEBUG("start : %d", *start);
	memcpy(page, mcdevs[0].name, mcdevs[0].count);
	*eof = 1;
	return mcdevs[0].count;
}
*/

static void *mcdev_seq_start(struct seq_file *s, loff_t *pos);
static void *mcdev_seq_next(struct seq_file *s, void *v, loff_t *pos);
static void *mcdev_seq_stop(struct seq_file *s, void *v);
static int mcdev_seq_show(struct seq_file *s, void *v);

static struct seq_operations mcdev_seq_ops = {
	.start	= mcdev_seq_start,
	.next	= mcdev_seq_next,
	.stop	= mcdev_seq_stop,
	.show	= mcdev_seq_show
};

static int mcdev_proc_open(struct inode *inode, struct file *filp);

static struct file_operations mcdev_proc_ops = {
	.owner	= THIS_MODULE,
	.open	= mcdev_proc_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release = seq_release
};


static int mcdev_proc_open(struct inode *inode, struct file *filp) {
	return seq_open(filp, &mcdev_seq_ops);
}

static void *mcdev_seq_start(struct seq_file *s, loff_t *pos) {
	if (*pos >= DEV_NUM) {
		return NULL;
	}
	//PDEBUG("seq_start : %d", *pos);
	//PDEBUG("mcdev addr: %p\n", mcdevs);
	return mcdevs + (*pos);
}

static void *mcdev_seq_next(struct seq_file *s, void *v, loff_t *pos) {
	(*pos)++;
	if (*pos >= DEV_NUM) {
		return NULL;
	}
	//PDEBUG("seq_next: %d", *pos);
	//PDEBUG("mcdev addr: %p\n", mcdevs+(*pos));
	return mcdevs + (*pos);
}

static void *mcdev_seq_stop(struct seq_file *s, void *v) {
	return NULL;
}


static int mcdev_seq_show(struct seq_file *s, void *v) {
	struct mcdev_data *data = (struct mcdev_data *)v;
	char *buf = NULL;
	if (down_interruptible(&data->sem)) {
		return -ERESTARTSYS;
	}
	buf = (char *)kmalloc(data->buf_size + 2, GFP_KERNEL);
	if (data == NULL) {
		return 1;
	}
	memset(buf, 0, data->buf_size + 2);
	memcpy(buf, data->buf, data->buf_size);
	//PDEBUG("count: %d name: %s\n",data->count, data->name);
	seq_printf(s, "%s\n", buf);
	up(&data->sem);
	kfree(buf);
	return 0;
}



/*
 *  device file operations
 */
int mcdev_open(struct inode *, struct file *);
int mcdev_release(struct inode *, struct file *);
ssize_t mcdev_read(struct file *, char __user *, size_t, loff_t *);
ssize_t mcdev_write(struct file *, const char __user *, size_t, loff_t *);
int mcdev_ioctl(struct inode *inode, struct file *filp,
		unsigned int cmd, unsigned long arg);

struct file_operations mcdev_ops = {
	.owner		= THIS_MODULE,
	.open		= mcdev_open,
	.release	= mcdev_release,
	.read		= mcdev_read,
	.write		= mcdev_write,
	.ioctl		= mcdev_ioctl,
};

int mcdev_ioctl(struct inode *inode, struct file *filp, 
		unsigned int cmd, unsigned long arg) {
	struct mcdev_data *data = &mcdevs[iminor(inode)];
	char *input_arg = NULL;
	int ret = 0;
	switch (cmd) {
	case MCDEV_IOCSETBUF:
		input_arg = (char *)arg;
		
		if (down_interruptible(&data->sem)) {
			return -ERESTARTSYS;
		}
		if ((data->buf == NULL) || (data->buf_size < strlen(input_arg))) {
			data->buf = (char *)kmalloc(strlen(input_arg), GFP_KERNEL);
			data->buf_size = strlen(input_arg);
		}
		memset(data->buf, 0, data->buf_size);
		ret = copy_from_user(data->buf, input_arg, data->buf_size);
		up(&data->sem);	
		break;
	default:
		return -EINVAL;	
	}
	return ret;
}

int mcdev_open(struct inode *inode, struct file *filp) {
	struct mcdev_data *data = NULL;
	
	PDEBUG("Open device %d:%d\n", imajor(inode), iminor(inode));

	if (filp->private_data == NULL) {
		data = container_of(inode->i_cdev, struct mcdev_data, mdev);
		if (data == NULL) {
			PDEBUG("Can not find the device %d:%d data", 
				imajor(inode), iminor(inode));
			return -EFAULT;
		}
		if (down_interruptible(&data->sem)) {
			return -ERESTARTSYS;
		}
		/*
		if (data->buf == NULL) {
			PDEBUG("malloc space");
			data->buf = (char *)kmalloc(strlen(INIT_DATA) + 1, GFP_KERNEL);
			if (data->buf == NULL) {
				PDEBUG("Can not malloc memory for buf ");
				return -1;
			}
			data->buf_size = strlen(INIT_DATA);
			memcpy(data->buf, INIT_DATA, data->buf_size);
		}
		*/
		up(&data->sem);
		filp->private_data = data;
	}
	PDEBUG("Device %d:%d buf: %s\n", 
		imajor(inode), iminor(inode), 
		((struct mcdev_data *)filp->private_data)->buf);
	PDEBUG("IOCTL CMD: %d", MCDEV_IOCSETBUF);
	return 0;
}

int mcdev_release(struct inode *inode, struct file *filp) {
	PDEBUG("Release device %d:%d\n", imajor(inode), iminor(inode));

	return 0; 
}

ssize_t mcdev_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	struct mcdev_data *data = (struct mcdev_data *)filp->private_data;
	int i = 0;
	int times = 0;
	int rest = 0;
	int ret = count;
	//PDEBUG("datacount = %d, count = %d , offp = %lld\n", data->count, count, *offp);
	/*
	if (!access_ok(VERIFY_READ, (void __user *)buff, count)) {
		return -EFAULT;
	}
	*/
	if (down_interruptible(&data->sem)) {
		return -ERESTARTSYS;
	}
	if (data->buf == NULL) {
		up(&data->sem);
		if (wait_event_interruptible(data->wait_queue, data->buf != NULL)) {
			return -ERESTARTSYS;
		}
		if (down_interruptible(&data->sem)) {
			return -ERESTARTSYS;
		}
	}
	times = count / data->buf_size;	
	rest = count - (times) * data->buf_size;

	for (i = 0; i < times; i++) {
		ret -= copy_to_user(buff, data->buf, data->buf_size);
	}

	ret -= copy_to_user(buff, data->buf, rest);
	up(&data->sem);
	*offp = 0;
	return ret;
}


ssize_t mcdev_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
	struct mcdev_data *data = (struct mcdev_data *)filp->private_data;
	int ret = count;
	/*
	if (!access_ok(VERIFY_WRITE, (void __user *)buff, count)) {
		return -EFAULT;
	}
	*/
	if (down_interruptible(&data->sem)) {
		return -ERESTARTSYS;
	}
	if (count > data->buf_size) {
		kfree(data->buf);
		data->buf = (char *)kmalloc(count, GFP_KERNEL);
		data->buf_size = count;
		memset(data->buf, 0, count);
		ret -= copy_from_user(data->buf, buff, count);
	}
	else {
		memset(data->buf, 0, data->buf_size);
		ret -= copy_from_user(data->buf, buff, count);
	}
	up(&data->sem);
	*offp = 0;
	wake_up_interruptible(&data->wait_queue);
	return ret;
}

/*
 * device add and del
 */
int add_mcdev(struct mcdev_data *data, struct file_operations *fops, int index){
	int ret = 0;
	dev_t dev_num = MKDEV(MAJOR(mcdev_num), index);
	//data->mdev = cdev_alloc();
	cdev_init(&(data->mdev), fops);
	(data->mdev).owner = THIS_MODULE;
	//(data->mdev)->ops = fops;
	init_MUTEX(&data->sem);
	init_waitqueue_head(&data->wait_queue);
	ret = cdev_add(&(data->mdev), dev_num, 1);
	return ret;	
}

void del_mcdev(struct mcdev_data *data) {
	if (data->buf != NULL) {
		kfree(data->buf);
	}
	cdev_del(&(data->mdev));
}

/*
 * module init and cleanup
 */

static int __init mcdev_init(void) {
	int result = 0;
	int i = 0;
	struct proc_dir_entry *entry;

	PDEBUG("Init device\n");
	result = alloc_chrdev_region(&mcdev_num, 0, DEV_NUM, DEV_NAME);
	
	if (result < 0) {
		PDEBUG("Can't alloc major number\n");
		return result;
	}
	PDEBUG("Alloc device number: %d\n", MAJOR(mcdev_num));

	for (i = 0; i < DEV_NUM; i++) {
		result = add_mcdev(&mcdevs[i], &mcdev_ops, i);
		if (result < 0) {
			PDEBUG("Create device %d error\n", i);
			return result;
		}
	}
	
	//create_proc_read_entry("mcdev", 0, NULL, mcdev_proc_read, NULL);
	
	entry = create_proc_entry("mcdev", 0, NULL);
	if (entry != NULL) {	
		entry->proc_fops = &mcdev_proc_ops;
	}
	
	return 0;
}

static void __exit mcdev_cleanup(void) {
	int i = 0;
	PDEBUG("cleanup device\n");
	PDEBUG("major %d minor: %d\n", MAJOR(mcdev_num), MINOR(mcdev_num));

	for (i = 0; i < DEV_NUM; i++) {
		del_mcdev(&mcdevs[i]);
	}

	remove_proc_entry("mcdev", NULL);
	unregister_chrdev_region(mcdev_num, DEV_NUM);
}

module_init(mcdev_init);
module_exit(mcdev_cleanup);
