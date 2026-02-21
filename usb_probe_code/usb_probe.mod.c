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
	{ 0xa728742c, "usb_register_driver" },
	{ 0x37a0cba, "kfree" },
	{ 0x28a823ab, "usb_find_interface" },
	{ 0x93c7edeb, "usb_find_common_endpoints" },
	{ 0x92997ed8, "_printk" },
	{ 0x7a01201a, "usb_bulk_msg" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x2cb2056d, "usb_register_dev" },
	{ 0x1e5b8225, "usb_deregister" },
	{ 0xc4a913aa, "__kmalloc_cache_noprof" },
	{ 0x3d38f36, "usb_deregister_dev" },
	{ 0x9f1dc8c6, "kmalloc_caches" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7121BC868FC0BE06F9FCB09");
