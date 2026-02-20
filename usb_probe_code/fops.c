#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/uaccess.h>
#include "driver.h"

static int usb_open(struct inode *inode, struct file *file) {
    struct usb_interface *interface;
    int minor;

    minor = iminor(inode);
    interface = usb_find_interface(&usb_skel_driver, minor);
    if (!interface) return -ENODEV;

    file->private_data = usb_get_intfdata(interface);
    return 0;
}

const struct file_operations fops_skel = {
    .owner = THIS_MODULE,
    .open = usb_open,
};
