#include <linux/module.h>
#include "driver.h"

static const struct usb_device_id usb_table[] = {
        { },
};
MODULE_DEVICE_TABLE(usb, usb_table);

static struct usb_driver usb_skel_driver = {
        .name       = "USB Skel",
        .probe      = usb_probe,
        .disconnect = usb_disconnect,
        .id_table   = usb_table,
};

MODULE_LICENSE("GPL");
module_usb_driver(usb_skel_driver);
