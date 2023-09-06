#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

#define DEBUG
#define BUF_LEN 80
static char Message[BUF_LEN];
static char *Message_Ptr;

static ssize_t driver_write(struct file* file, const char* buffer, size_t length, loff_t *offs){
        int i = 0;

        #ifdef DEBUG
        printk ("device_write(%p,%s,%d)", file, buffer, length);
        #endif
        for(i=0; i<length && i<BUF_LEN; i++){
                get_user(Message[i],buffer+i);
        }

        Message_Ptr = Message;
        /* Again, return the number of input characters used */
        return i;
}

static ssize_t driver_read(struct file* file, char* buffer, size_t length, loff_t *offs){
        /* Number of bytes actually written to the buffer */
        int bytes_read = 0;

        #ifdef DEBUG
        printk("device_read(%p,%p,%d)\n", file, buffer, length);
        #endif
        /* If we're at the end of the message, return 0
        * (which signifies end of file) */
        if (*Message_Ptr == 0) return 0;

        /* Actually put the data into the buffer */
        while (length && *Message_Ptr)  {

                /* Because the buffer is in the user data segment,
                * not the kernel data segment, assignment wouldn't
                * work. Instead, we have to use put_user which
                * copies data from the kernel data segment to the
                * user data segment. */
                put_user(*(Message_Ptr++), buffer++);
                length--;
                bytes_read ++;
        }

        #ifdef DEBUG
        printk ("Read %d bytes, %d left\n", bytes_read, length);
        #endif
        /* Read functions are supposed to return the number
        * of bytes actually inserted into the buffer */
        return bytes_read;
}

static ssize_t close_driver(struct inode* device_file, struct file* instance){
        printk("close driver!!!\n");
        return 0;
}

static ssize_t open_driver(struct inode* device_file, struct file* instance){
        printk("open driver!!!\n");
        return 0;
}

static struct file_operations fops = {
        .owner = THIS_MODULE,
        .open = open_driver,
        .release =  close_driver,
        .read = driver_read,
	.write = driver_write
};

static int __init ModuleInit(void){
        register_chrdev(64,"gpu_dev",&fops);
        return 0;
}

static void __exit ModuleExit(void){
        unregister_chrdev(64,"gpu_dev");
}


module_init(ModuleInit);
module_exit(ModuleExit);