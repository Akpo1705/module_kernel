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
	{ 0xc1514a3b, "free_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0xa536e7b7, "gpiod_to_irq" },
	{ 0xf1f0ee9b, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x90accf5a, "gpiod_direction_input" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xad914b66, "gpiod_set_raw_value" },
	{ 0xa0ff6b02, "gpiod_get_raw_value" },
	{ 0x702409be, "gpio_to_desc" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "F86F52E2D86A6F58FBE6C25");
