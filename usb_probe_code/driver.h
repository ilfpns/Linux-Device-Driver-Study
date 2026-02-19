#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <linux/usb.h>
#include <linux/types.h>

struct usb_pack {
	__u8 bulk_in;
	__u8 bulk_out;
};

int usb_probe(struct usb_interface *interface, const struct usb_device_id *id);
void usb_disconnect(struct usb_interface *interface);

#endif
