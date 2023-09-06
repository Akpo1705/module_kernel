#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xa87151c7, "module_layout" },
	{ 0xb959c7fe, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe01245aa, "class_destroy" },
	{ 0xf73c6013, "device_destroy" },
	{ 0xfe990052, "gpio_free" },
	{ 0x90accf5a, "gpiod_direction_input" },
	{ 0xf1f0ee9b, "gpiod_direction_output_raw" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xe9d7a119, "cdev_add" },
	{ 0x1069c01a, "cdev_init" },
	{ 0x49930630, "device_create" },
	{ 0xa42e0aca, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xad914b66, "gpiod_set_raw_value" },
	{ 0x5f754e5a, "memset" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xa0ff6b02, "gpiod_get_raw_value" },
	{ 0x702409be, "gpio_to_desc" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "10B263D126671ED840BB499");
