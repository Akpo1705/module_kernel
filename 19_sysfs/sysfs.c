#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anokhin");
MODULE_DESCRIPTION("Creating a folder and a file in sysfs");

static struct kobject *alex_kobj;

static ssize_t alex_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer){
	return sprintf(buffer, "You have read from /sys/kernel/%s/%s\n", kobj->name, attr->attr.name);
}

static ssize_t alex_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count){
	printk("sysfs_test - You wrote '%s' to /sys/kernel/%s/%s\n", buffer, kobj->name, attr->attr.name);
	return count;
}

static struct kobj_attribute alex_attr = __ATTR(alex,0660,alex_show,alex_store);

static int __init ModuleInit(void){
	printk("Hello!\n");
	printk("sysfs_test - Creating /sys/kernel/hello/alex\n");

	alex_kobj = kobject_create_and_add("alex_sys",kernel_kobj);
	if(!alex_kobj){
		printk("sysfs test - Error creating /sys/kernel/hello\n");
		return -ENOMEM;
	}

	if(sysfs_create_file(alex_kobj, &alex_attr.attr)){
		printk("sysfs_test - Error creating /sys/kernel/hello/alex\n");
		kobject_put(alex_kobj);
		return -ENOMEM;
	}

	return 0;
}

static void __exit ModuleExit(void){
	printk("sysfs_test - Remove /sys/kernel/hello/alex\n");
	sysfs_remove_file(alex_kobj,&alex_attr.attr);
	kobject_put(alex_kobj);
	printk("Done!\n");
}


module_init(ModuleInit);
module_exit(ModuleExit);
