#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>

#include <linux/gpio/consumer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");
MODULE_DESCRIPTION("Control LED");

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.wrtie = driver_write
}

static int driver_open (struct inode *, struct file *) {
	printk("파일 드라이버 열림!\n");
	return 0;
}

static int driver_close (struct inode *, struct file *) {
	printk("파일 드라이버 종료\n");
	return 0;
}
