#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

#define DRIVER_NAME  "testGPIO_Driver"
#define DRIVER_CLASS "TestModuleClass"

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");
MODULE_DESCRIPTION("Control Led, input Button");

/* open */
static int driver_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "driver_open\n");
    return 0;
}

/* close */
static int driver_close(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "driver_close\n");
    return 0;
}

/* read */
static ssize_t driver_read(struct file *file,
                           char __user *user_buffer,
                           size_t count,
                           loff_t *offset)
{
    int to_copy, not_copied;

    to_copy = min(count, (size_t)buffer_pointer);
    not_copied = copy_to_user(user_buffer, buffer, to_copy);

    return to_copy - not_copied;
}

/* write */
static ssize_t driver_write(struct file *file,
                            const char __user *user_buffer,
                            size_t count,
                            loff_t *offset)
{
    int to_copy, not_copied;

    to_copy = min(count, sizeof(buffer));
    not_copied = copy_from_user(buffer, user_buffer, to_copy);
    buffer_pointer = to_copy;

    return to_copy - not_copied;
}

/* file operations */
static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = driver_open,
    .release = driver_close,
    .read    = driver_read,
    .write   = driver_write,
};

/* module init */
static int __init ModuleInit(void)
{
    printk(KERN_INFO "Init testDriver\n");

    if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0)
        return -1;

    my_class = class_create(DRIVER_CLASS);
    if (IS_ERR(my_class))
        goto err_class;

    if (IS_ERR(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME)))
        goto err_device;

    cdev_init(&my_device, &fops);
    if (cdev_add(&my_device, my_device_nr, 1) < 0)
        goto err_cdev;

    if (gpio_request(14, "rpi-gpio-14")) {
	    printk("failed allocate 14\n");
	    goto Gpio14Error;
    }

    if (gpio_direction_output(14, 0)) {
	    printk("failed set 14\n");
	    goto Gpio14Error;
    }

    if (gpio_request(15, "rpi-gpio-15")) {
            printk("failed allocate 14\n");
            goto Gpio15Error;
    }
 
      if (gpio_direction_output(15, 0)) {
            printk("failed set 14\n");
            goto Gpio15Error;
    }


    return 0;

err_cdev:
    device_destroy(my_class, my_device_nr);
err_device:
    class_destroy(my_class);
err_class:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;
Gpio15Error:
    gpio_free(15);
Gpio14Error:
    gpio_free(14);
}

/* module exit */
static void __exit ModuleExit(void)
{
   gpio_set_value(14, 0);
   gpio_free(15);
   gpio_free(14);

    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    printk(KERN_INFO "Exit testDriver\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
