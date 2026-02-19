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
	{ 0x92997ed8, "_printk" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xa01f13a6, "cdev_init" },
	{ 0x3a6d85d3, "cdev_add" },
	{ 0xdeea99cc, "device_destroy" },
	{ 0x59c02473, "class_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe9d4f7c9, "device_create" },
	{ 0x6775d5d3, "class_destroy" },
	{ 0x27271c6b, "cdev_del" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x1000e51, "schedule" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xdcb764ad, "memset" },
	{ 0xe2964344, "__wake_up" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "6031C69650E0A6542E10E5A");
