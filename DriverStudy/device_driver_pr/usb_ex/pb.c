#include <linux/module.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ilfpns");

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id);

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id) {
	struct usb_device *udev;
	struct usb_endpoint_descriptor *bulk_in = NULL;
	struct usb_endpoint_descriptor *bulk_out = NULL;
	int retval;

	udev = interface_to_usbdev(interface);
	pr_info("USB device 연결\n");
	pr_info("VID : %04x, PID : %04x\n", 
		le16_to_cpu(udev->descriptor.idVendor),
		le16_to_cpu(udev->descriptor.idProduct));
}

static struct usb_driver usb_skel_driver = {
	.name = "USB Skel",
	.probe = usb_probe,
};

module_usb_driver(usb_skel_driver);
