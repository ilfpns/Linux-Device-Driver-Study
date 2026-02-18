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
	struct usb_endpoint_descriptor *bulk_in = NULL;  // USB에서 들어오는 bulk data 저장
	struct usb_endpoint_descriptor *bulk_out = NULL; // USB로 나가는 bulk data 저
	int retval;

	udev = interface_to_usbdev(interface);
	pr_info("USB device 연결\n");
	pr_info("VID : %04x, PID : %04x\n", 
		// endian convention
		le16_to_cpu(udev->descriptor.idVendor),    // VID, 제조사 번호
		le16_to_cpu(udev->descriptor.idProduct));  // PID, 고유 번호
	pr_info("Interface Class : 0x%02x\n",
		interface->cur_altsetting->desc.bInterfaceClass);

	retval = usb_find_common_endpoints(interface->cur_altsetting, &bulk_in, &bulk_out, NULL, NULL);
	if (retval) {
		pr_info("No bulk endpoints를 찾을 수 없음\n");
		return 0;
	}

	pr_info("bulk IN  endpoint AD : 0x%02x\n", bulk_in->bEndpointAddress);   // USB -> PC
	pr_info("bulk max packet size : %d\n", usb_endpoint_maxp(bulk_in));      // 데이터 이동 단위
	pr_info("bulk OUT endpoint AD : 0x%02x\n", bulk_out->bEndpointAddress);  // PC -> USB
	return 0;
}

static struct usb_driver usb_skel_driver = {
	.name = "USB Skel",
	.probe = usb_probe,
};

module_usb_driver(usb_skel_driver);
