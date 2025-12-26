#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>   
#include <linux/kernel.h>

static const struct file_operations misc_fops = {
	.owner = THIS_MODULE,
	.open = misc_open,
}

static int misc_open(struct inode * inode, struct file *file) {
	printk("misc 열림");
	return 0;
}

static int misc_close(struct inode *inode, struct file *file) {
	printk("misc close 호출");
	return 0;
}

static int __init misc_init(void) {
	printk("misc 초기화");
	int retval;
	retval = register_chrdev(DD_MAJOR, "dev_br", &fops);
	return 0;
}

static void __exit misc_exit(void) {
	unregister_chrdev(0, "dev_nr");
	printk("misc 탈출");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");
