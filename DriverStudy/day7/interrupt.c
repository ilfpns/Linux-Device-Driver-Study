#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>

#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/minmax.h>

#include <linux/gpio/consumer.h>

#define DRIVER_NAME "testDriver"
#define DRIVER_CLASS "TestModuleClass"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");
MODULE_DESCRIPTION("Control LED");

static int driver_open(struct inode *, struct file *);
static int driver_close(struct inode *, struct file *);
static ssize_t driver_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t driver_write(struct file *, const char __user *, size_t, loff_t *);

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

static char buffer[256];
static size_t buffer_pointer;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.write = driver_write
};

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
ssize_t driver_read (struct file *File, char __user *user_buffer, size_t count, loff_t *offs) {
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
static int __init my_driver_init(void) {
	printk("드이버 초기화\n");
	
	// major, minor 값 받아오기
	if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0 ) {
		printk("allocated 실패 \n");
		return -1;
	}

	printk("major : %d, minor : %d \n", MAJOR(my_device_nr), MINOR(my_device_nr));

	cdev_init(&my_device, &fops);
 
        if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
                device_destroy(my_class, my_device_nr);
        }

	// 커널에 디바이스 분류용 class를 하나 생성
	// dev에 주소를 만들기만 함
	if ((my_class = class_create(DRIVER_CLASS)) == NULL) {
		printk("class 생성 실패 \n");
		unregister_chrdev_region(my_device_nr, 1);
		return -1;
	}
	
	// 주소에 가서 device 생성
	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("device 생성 실패 \n");
		class_destroy(my_class);

		unregister_chrdev_region(my_device_nr, 1);
   		 return -1;
	}
        
        return 0;
}

static void __exit my_driver_exit(void) {
	printk("드라이버 탈출\n");

	cdev_del(&my_device);
        device_destroy(my_class, my_device_nr);
     	unregister_chrdev_region(my_device_nr, 1);
     	class_destroy(my_class);
        printk("드라이버 초기호 끝, 탈출\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);
