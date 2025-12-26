#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
// MODULE_AUTHOR(“Johannes 4 GNU/Linux”); refer source site
MODULE_AUTHOR("Student 4 GNU/Linux");
MODULE_DESCRIPTION("Hello World Day1");

static int __init driver_init(void) {
	printk("Hello \n");
	return 0;
}

static void __exit driver_exit(void) {
	printk("Bye \n");
}

module_init(driver_init);
module_exit(driver_exit);
