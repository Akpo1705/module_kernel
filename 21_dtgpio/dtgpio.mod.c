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
	{ 0x8181429f, "platform_driver_unregister" },
	{ 0xb9a12f50, "__platform_driver_register" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x5304b6cd, "proc_create" },
	{ 0xbef6dceb, "gpiod_get" },
	{ 0x3c9a6114, "device_property_read_u32_array" },
	{ 0xc5c2f66a, "device_property_read_string" },
	{ 0x14539eee, "device_property_present" },
	{ 0x51559d99, "gpiod_set_value" },
	{ 0x230d7d1f, "proc_remove" },
	{ 0x985277ed, "gpiod_put" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cbrightlight,mydev");
MODULE_ALIAS("of:N*T*Cbrightlight,mydevC*");

MODULE_INFO(srcversion, "037C0734178F9B779DDF6BF");
