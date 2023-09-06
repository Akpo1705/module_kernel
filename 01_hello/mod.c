#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>


static void sayHello(void)
{
	printk(KERN_INFO"Hello world\n");
}

EXPORT_SYMBOL(sayHello);
static int __init hello_init(void)
{
	sayHello();
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO"Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");