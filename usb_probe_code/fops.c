#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/uaccess.h>
#include "driver.h"

static int usb_open (struct inode *inode, struct file *file) {
    struct usb_interface *interface;
    int minor;

    minor = iminor(inode);
    interface = usb_find_interface(&usb_skel_driver, minor);
    if (!interface) return -ENODEV;

    file->private_data = usb_get_intfdata(interface);
    return 0;
}

static ssize_t usb_read(struct file *file, char __user *user_data, size_t count, loff_t *loff) {
    struct usb_pack *pack;
    struct usb_device *udev;
    int retval;
    int length;
    unsigned char *kbuf;

    pack = file->private_data;
    udev = pack->udev;

    kbuf = kmalloc(64, GFP_KERNEL);
    if (!kbuf) return -ENOMEM;

    retval = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, pack->bulk_in), kbuf, 64, &length, 5000);
    if (retval == 0) {
        if (copy_to_user(user_data, kbuf, length)) 
            retval = -EFAULT;
        else
            retval = length;
    }

    kfree(kbuf);
    return retval;

}

const struct file_operations fops_skel = {
    .owner = THIS_MODULE,
    .open = usb_open,
    .read = usb_read,
};
