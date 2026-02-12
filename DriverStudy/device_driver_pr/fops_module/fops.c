#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/usb.h>	 // usb stuff
#include <linux/errno.h> // pr_err()
#include <asm/uaccess.h> // copy_to_user(), copy_from_user() 
#include <linux/slab.h>  // kalloc()

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");

struct usb_nr {
        char testbuff[6];
        char lenbuff;
        struct usb_endpoint_descriptor  *int_in_endpoint;
        struct usb_endpoint_descriptor  *int_out_endpoint;
};

void free_usb_nr(struct usb_nr *dev){
        printk("_NR_ free_usb_nr()\n");
        kfree(dev);
};

static struct usb_driver nr_driver;

static int nr_open (struct inode  *inode, struct file *filp);

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = nr_open,
};

static int nr_open (struct inode  *inode, struct file *filp) {
	struct usb_nr *dev = NULL;
	int retval = 0;
	int subminor;
	struct usb_interface *interface;
	printk("nr_open 열림\n");

	subminor = iminor(inode);
	interface = usb_find_interface(&nr_driver, subminor);

	if (!interface) {
		pr_err("_NR_%s - error, minor(%d)  디바이스 찾지 못함\n", __func__, subminor);
		retval = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(interface);
	if (!dev) {
		retval = -ENODEV;
		goto exit;
	}
	
	// TEST print
	dev->testbuff[0] = 'H';
	dev->testbuff[1] = 'i';
	dev->testbuff[2] = ' ';
	dev->testbuff[3] = 'N';
	dev->testbuff[4] = 'R';
	dev->testbuff[5] = '\n';
	dev->lenbuff = 6;

	filp->private_data = dev;
	printk("nr_open 종료\n");
exit:
	return retval;

}

static int __init nr_init (void) {
	printk("모듈 올리기 성공\n");
	return 0;
}

static void __exit nr_exit (void) {
	printk("모듈 내리기 성공\n");
	return;
}

module_init(nr_init);
module_exit(nr_exit);

