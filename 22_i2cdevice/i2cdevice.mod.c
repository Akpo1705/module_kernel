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
	{ 0x661b0fef, "i2c_del_driver" },
	{ 0xa86698a4, "i2c_register_driver" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xe8a53de4, "i2c_smbus_read_byte" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xecd021eb, "i2c_smbus_write_byte" },
	{ 0xaa19e4aa, "_kstrtol" },
	{ 0x5304b6cd, "proc_create" },
	{ 0x230d7d1f, "proc_remove" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:my_adc");
MODULE_ALIAS("of:N*T*Cbridglight,myadc");
MODULE_ALIAS("of:N*T*Cbridglight,myadcC*");

MODULE_INFO(srcversion, "8824B9F4406783A0B7F5EE8");
