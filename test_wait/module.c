#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/sched.h>

#include <linux/wait.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anokhin");
MODULE_DESCRIPTION("Kernel module wich use poll to notify an userspace app when GPIO 17 hs a rising edge");

#define MYMAJOR 65

DECLARE_WAIT_QUEUE_HEAD(wq1);
static int flag = 0;

static int mod_write(struct file* file,const char* buffer, size_t length, loff_t *offs){
	printk(KERN_DEBUG "process %i (%s) awakening the readers...\n", current->pid, current->comm);
    flag = 1;
    wake_up_interruptible(&wq1);
    return length; /* успешно, избегаем повтора */
}

static int mod_read(struct file* file, char* buffer, size_t length, loff_t *offs){

	printk(KERN_DEBUG "process %i (%s) going to sleep\n", current->pid, current->comm);
    wait_event_interruptible(wq1, flag != 0);
    flag = 0;
    printk(KERN_DEBUG "awoken %i (%s)\n", current->pid, current->comm);
    return 0; /* конец файла */
}

static struct file_operations fops = {
		.owner = THIS_MODULE,
		.write = mod_write,
		.read = mod_read,
};

static int __init ModuleInit(void){
	printk("Hello!\n");

	register_chrdev(MYMAJOR,"mod",&fops);

	return 0;
}

static void __exit ModuleExit(void){
	unregister_chrdev(MYMAJOR,"mod");
	printk("Done!\n");
}


module_init(ModuleInit);
module_exit(ModuleExit);
