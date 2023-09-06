#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/sched/signal.h>
#include <linux/ioctl.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anokhin GNU/Linux");
MODULE_DESCRIPTION("Kernel Module which sends a signal to an userspace app when GPIO 17 has a rising edge");

unsigned int irq_number;
/* define for Signal sending */
#define SIGNR 44
#define REGISTER_UAPP _IO('R','g')
#define MYMAJOR 64
static struct task_struct *task = NULL;

static irq_handler_t gpio_irq_signal_handler(unsigned int irq, void *dev_id, struct pt_regs *resg){
        struct siginfo info;
        printk("gpio_irq_signal: Interrupt was triggered and ISR was called!\n");

        if(task != NULL){
                memset(&info, 0, sizeof(info));
                info.si_signo = SIGNR;
                info.si_code = SI_QUEUE;

                if(send_sig_info(SIGNR, (struct kernel_siginfo *) &info, task) < 0)
                        printk("gpio_irq_signal: Error sending signal\n");
        }
        return (irq_handler_t) IRQ_HANDLED;
}

static int signal_close(struct inode *device_file, struct file* instance){
        if(task != NULL)
                task = NULL;

        return 0;
}

static long int signal_ioctl(struct file *file, unsigned cmd, unsigned long arg){

        if(cmd == REGISTER_UAPP){
                task = get_current();
                printk("gpio_irq_signal: Userspace app with PID %d is registered\n", task->pid);
        }

        return 0;
}

static struct file_operations fops = {
        .owner = THIS_MODULE,
        .release = signal_close,
        .unlocked_ioctl = signal_ioctl,
};

static int __init ModuleInit(void){
        printk("qpio_irq: Loading module... ");

        if(gpio_request(17, "rpi-gpio-17")){
                printk("Error!\n Can not allocate GPIO 17\n");
                return -1;
        }

        if(gpio_direction_input(17)){
                printk("Error!\nCan not set GPIO 17 to input!\n");
                gpio_free(17);
                return -1;
        }

        gpio_set_debounce(17, 700);

        irq_number = gpio_to_irq(17);

        if(request_irq(irq_number, (irq_handler_t) gpio_irq_signal_handler, IRQF_TRIGGER_RISING, "gpio_irq_signal", NULL) != 0){
                printk("Error!\nCan not request interrupt nr.: %d\n", irq_number);
                gpio_free(17);
                return -1;
        }

        if(register_chrdev(MYMAJOR, "gpio_sig_dev", &fops) < 0){
                printk("Error!\nCan't register device Number !\n");
                gpio_free(17);
                free_irq(irq_number,NULL);
        }

        printk("Done!\n");
        printk("GPIO 17 is mapped to IRQ Nr.: %d\n", irq_number);
        return 0;

        return 0;
}

static void __exit ModuleExit(void){
        printk("gpio_irq_signal: Unloading module....\n");
        free_irq(irq_number, NULL);
        gpio_free(17);
        unregister_chrdev(MYMAJOR,"gpio_sig_dev");
        printk("Done!n");
}

module_init(ModuleInit);
module_exit(ModuleExit);







