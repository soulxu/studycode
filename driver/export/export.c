#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/proc_fs.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

#define METHOD_SIMPLE	"simple"
#define METHOD_SEQ	"seq"

static char *method = METHOD_SIMPLE;

module_param(method, charp, S_IRUGO);

//simple

static int export_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data) {
	struct list_head *ptr = &(current->tasks);
	struct task_struct *task = NULL;
	char buf[4096] = { 0 };
	int len = 0;

	list_for_each(ptr, &(current->tasks)) {
		task = list_entry(ptr, struct task_struct, tasks);
		sprintf(buf, "command: %s\n", task->comm);
		len += strlen(buf);

		if ((len > count) || (len > 4096)) {
			*start = len;
			return len;
		}

		strcpy(page, buf);				
		page += strlen(buf);
	}

	*eof = 1;
	return len;	
}

//seq 
struct task_list {
	struct list_head *cur;
	struct list_head *head;
};

static void *export_seq_start(struct seq_file *m, loff_t *pos) {
	printk(KERN_ALERT "seq start.\n");
	struct task_list *list = kmalloc(sizeof(struct task_list), GFP_KERNEL);
	list->head = list->cur = &(current->tasks);
	return list;
}

static void export_seq_stop(struct seq_file *m, void *v) {
	printk(KERN_ALERT "seq stop.\n");
	kfree((struct task_list *)v);
}

static void *export_seq_next(struct seq_file *m, void *v, loff_t *pos) {
	printk(KERN_ALERT "seq next.\n");
	struct task_list *list = (struct task_list *)v;
	list->cur = list->cur->next;

	if (list_is_last(list->cur, list->head)) {
		printk(KERN_ALERT "list end\n");
		return NULL;
	}

	return list;
}

static int export_seq_show(struct seq_file *m, void *v) {
	printk(KERN_ALERT "seq show.\n");
	struct task_list *list = (struct task_list *)v;

	if (list == NULL) {
		return -1;
	}	

	struct task_struct *task = list_entry(list->cur, struct task_struct, tasks);
	seq_printf(m, "command: %s\n", task->comm);
	return 0;
}

static struct proc_dir_entry *proc_entry;

static struct seq_operations export_seq_ops = {
	.start	= export_seq_start,
	.stop	= export_seq_stop,
	.next	= export_seq_next,
	.show	= export_seq_show
};

static int export_seq_open(struct inode *inode, struct file *filp) {
	return seq_open(filp, &export_seq_ops);
}

static struct file_operations export_proc_ops = {
	.owner	= THIS_MODULE,
	.open	= export_seq_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release= seq_release
};

static int export_init(void) {
	if (strcmp(method, METHOD_SIMPLE) == 0) {
		proc_entry = create_proc_read_entry("export_simple", 
			0, 
			NULL, 
			export_proc_read, 
			NULL);
	}
	else if (strcmp(method, METHOD_SEQ) == 0) {
		proc_entry = proc_create_data("export_seq", 
			0, 
			NULL, 
			&export_proc_ops, 
			NULL);
	}
	else {
		printk(KERN_ERR "unkown method.\n");
		return -1;
	}

	if (proc_entry == NULL) {
		printk(KERN_ERR "can not create entry.\n");
		return -1;
	}

	return 0;
}

static void export_exit(void) {
	if (strcmp(method, METHOD_SIMPLE) == 0) {
		remove_proc_entry("export_simple", NULL);
	}	
	else if (strcmp(method, METHOD_SIMPLE) == 0) {
		
	}
}

module_init(export_init);
module_exit(export_exit);
