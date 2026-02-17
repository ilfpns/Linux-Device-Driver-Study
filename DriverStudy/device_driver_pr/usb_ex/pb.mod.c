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
	{ 0x92997ed8, "_printk" },
	{ 0x61fd46a9, "platform_driver_unregister" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Ctest,myprobe");
MODULE_ALIAS("of:N*T*Ctest,myprobeC*");

MODULE_INFO(srcversion, "92E84D2E16AE66003451F27");
