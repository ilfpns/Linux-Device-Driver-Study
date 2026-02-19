#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xfa474811, "__platform_driver_register" },
	{ 0x4df83a8d, "gpiod_set_value" },
	{ 0x92997ed8, "_printk" },
	{ 0x3250fd9c, "devm_gpiod_get" },
	{ 0x61fd46a9, "platform_driver_unregister" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cmycompany,gpio-led");
MODULE_ALIAS("of:N*T*Cmycompany,gpio-ledC*");

MODULE_INFO(srcversion, "2517204DCFF442AFDEE4D21");
