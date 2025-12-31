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
	.write = driver_write
}
// open & close
static int driver_open (struct inode *Inode, struct file *File) {
	printk("파일 드라이버 열림!\n");
	return 0;
}

static int driver_close (struct inode *Inode, struct file *File) {
	printk("파일 드라이버 종료\n");
	return 0;
}

// read & write
ssize_t driver_read (struct file *File, char user *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;

	to_copy = min(count, buffer_pointer);
	not_copied = copy_to_user(user_buffer, buffer, to_copy);
	
	delta = to_copy - not_copied;
	printk("테스트 드라이버 Read함수 \n");
	return delta;
}

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;

	to_copy = min(count, sizeof(buffer));
	not_copied = copy_from_user(buffer, user_buffer, to_copy);
	buffer_pointer = to_copy;

	delta = to_copy - not_copied;
	printk("테스트 드라이버 write함수 \n");

	return delta;
}

// init & exit
static int __init driver_init(void) {
	printk("드이버 초기화\n");
	return 0;
}

static void __exit driver_exit(void) {
	printk("드라이버 탈출\n");
}

module_init(driver_init);
module_eixt(driver_eixt);

MODULE_LICENSE("GPL");
