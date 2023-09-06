#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
// #include <linux/jiffies.h>
// #include <linux/timer.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple test for LKM's timer");

static struct timer_list my_timer;
static struct timer_list my_2_timer;


void timer_callback(struct timer_list * data) {
	gpio_set_value(4, 0); /* Turn LED off */
}

void timer_callback_2(struct timer_list * data) {
	gpio_set_value(4, 1); /* Turn LED off */
}

static int __init ModuleInit(void){
        printk("Hello, Kernel!\n");

        if(gpio_request(4, "rpi-gpio-4")){
                printk("Cant not allocate GPIO4\n");
                return -1;
        }

	/* Set GPIO 4 direction */
	if(gpio_direction_output(4, 0)) {
		printk("Can not set GPIO 4 to output!\n");
		gpio_free(4);
		return -1;
	}



        gpio_set_value(4, 1);

        timer_setup(&my_timer, timer_callback, 0);
        timer_setup(&my_2_timer, timer_callback_2, 0);
        mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
        mod_timer(&my_2_timer, jiffies + msecs_to_jiffies(2000));

        return 0;
}

static void __exit ModuleExit(void) {
	printk("Goodbye, Kernel\n");
	gpio_free(4);
	del_timer(&my_timer);
        del_timer(&my_2_timer);
}

module_init(ModuleInit);
module_exit(ModuleExit);