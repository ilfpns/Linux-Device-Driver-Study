#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");

static int __init my_init (void) {
	printk("모듈 올리기 성공\n");
	return 0;
}

static void __exit my_exit (void) {
	printk("모듈 내리기 성공\n");
	return;
}

module_init(my_init);
module_exit(my_exit);

