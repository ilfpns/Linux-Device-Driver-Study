#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <linux/usb.h>
#include <linux/types.h>
#include <linux/usb.h>

extern struct usb_driver usb_skel_driver;

struct usb_pack {
    struct usb_device *udev;
    __u8 bulk_in;
	__u8 bulk_out;
};

int usb_probe(struct usb_interface *interface, const struct usb_device_id *id);
void usb_disconnect(struct usb_interface *interface);

extern const struct file_operations fops_skel;
#endif
