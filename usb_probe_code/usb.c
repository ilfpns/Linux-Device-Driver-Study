#include <linux/module.h>
#include <linux/types.h>
#include "driver.h"
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/slab.h>

int usb_probe(struct usb_interface *interface, const struct usb_device_id *id) {
	struct usb_device *udev;
	struct usb_endpoint_descriptor *bulk_in = NULL;  // USB에서 들어오는 bulk data 저장
	struct usb_endpoint_descriptor *bulk_out = NULL; // USB로 나가는 bulk data 저
	int retval;
	struct usb_pack *my_usb_pack;

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
		return -ENODEV;
	}
	
	my_usb_pack = kzalloc(sizeof(struct usb_pack), GFP_KERNEL);
	if (!my_usb_pack) {
		return -ENOMEM;
	}

	my_usb_pack->bulk_in = bulk_in->bEndpointAddress;
	my_usb_pack->bulk_out = bulk_out->bEndpointAddress;
	usb_set_intfdata(interface, my_usb_pack);	

	pr_info("bulk IN  endpoint AD : 0x%02x\n", bulk_in->bEndpointAddress);   // USB -> PC
	pr_info("bulk max packet size : %d\n", usb_endpoint_maxp(bulk_in));      // 데이터 이동 단위
	pr_info("bulk OUT endpoint AD : 0x%02x\n", bulk_out->bEndpointAddress);  // PC -> USB
	return 0;
}

void usb_disconnect(struct usb_interface *interface) {
	struct usb_pack *my_usb_pack;
	my_usb_pack = usb_get_intfdata(interface);

	kfree(my_usb_pack);
	usb_set_intfdata(interface, NULL);
	pr_info("USB 연결 해제 및 메모리 해제\n");	
}
