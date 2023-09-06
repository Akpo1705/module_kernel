#include <linux/module.h>
#include <linux/init.h>
//#include <linux/gpio.h>
//#include <linux/cdev.h>
//#include <linux/fs.h>
//#include <linux/ioctl.h>
//#include <linux/interrupt.h>
//#include <linux/kthread.h>
//#include <linux/sched.h>

//#include <linux/wait.h>

#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anokhin");
MODULE_DESCRIPTION("Kernel module wich use poll to notify an userspace app when GPIO 17 hs a rising edge");

static struct proc_dir_entry *proc_folder;
static struct proc_dir_entry *proc_file;

static ssize_t mod_write(struct file* file,const char* buffer, size_t length, loff_t *offs){

	char text[255];
	int to_copy,not_copied,delta;

	memset(text,0,sizeof(text));

	to_copy = min(length,sizeof(text));

	not_copied = copy_from_user(&text,buffer,to_copy);

	printk("procfs_test - You have written %s to me\n", text);

	delta = to_copy - not_copied;

	return delta;
}

static ssize_t mod_read(struct file* file, char* buffer, size_t length, loff_t *offs){

	char buf[] = "Hello from proc file\n";
	int copy_to, not_copied, delta;

	copy_to = min(length,sizeof(buf));

	not_copied = copy_to_user(buffer,&buf,copy_to);

	delta = copy_to - not_copied;

        return delta;
}

static struct proc_ops fops = {
		.proc_write = mod_write,
		.proc_read = mod_read,
};

static int __init ModuleInit(void){
	printk("Hello!\n");

	proc_folder = proc_mkdir("hello",NULL);
	if(proc_folder == NULL){
		printk("procfs_test - Error creating /proc/hello\n");
		return -ENOMEM;
	}

	proc_file = proc_create("alex",0666, proc_folder,&fops);
	if(proc_file == NULL){
		printk("proc_file - Error creating file /proc/hello/alex\n");
		proc_remove(proc_folder);
		return -ENOMEM;
	}

	printk("procfs_test - Create /proc/hello/alex\n");

	return 0;
}

static void __exit ModuleExit(void){
	printk("procfs_test - Remove /proc/hello/alex\n");
	proc_remove(proc_folder);
	proc_remove(proc_file);
	printk("Done!\n");
}


module_init(ModuleInit);
module_exit(ModuleExit);
