#include <linux/module.h>
#include <linux/usb.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/hid.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

#define USB_SAMPLE_VENDOR_ID 0x04fc
#define USB_SAMPLE_PRODUCT_ID 0x05d8


static struct usb_device_id usb_sample_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT, USB_INTERFACE_PROTOCOL_MOUSE) },
	{ }
};

MODULE_DEVICE_TABLE(usb, usb_sample_table);

static int usb_sample_probe(struct usb_interface *interface, const struct usb_device_id *id);

static void usb_sample_disconnect(struct usb_interface *interface);

static struct usb_driver usb_sample_driver = {
	.name = "usb_sample",
	.id_table = usb_sample_table,
	.probe = usb_sample_probe,
	.disconnect = usb_sample_disconnect,
};

struct usb_mouse {
	struct urb *irq;
	char *data;
	dma_addr_t data_dma;
	
};

static struct usb_sample_dev {
	struct usb_mouse *mouse;
} sample_dev;

int usb_sample_open(struct inode *inode, struct file *filp) {
	printk(KERN_DEBUG "open\n");
	
	if (usb_submit_urb(sample_dev.mouse->irq, GFP_KERNEL)) {
		return -EIO;
	}

	return 0;
}

int usb_sample_release(struct inode *inode, struct file *filp) {
	printk(KERN_DEBUG "release\n");
	usb_kill_urb(sample_dev.mouse->irq);
	return 0;
}

static struct file_operations usb_sample_fops = {
	.open = usb_sample_open,
	.release = usb_sample_release
};

static struct usb_class_driver usb_sample_class = {
	.name="sample%d",
	.fops = &usb_sample_fops,
	//.mode = S_IFCHR | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH,
	.minor_base = 0
};

static void usb_mouse_irq(struct urb *urb) {
	struct usb_mouse *mouse = urb->context;
	int status = 0;
	char *data = mouse->data;
	printk(KERN_DEBUG "urb status: %d\n", urb->status);

	switch (urb->status) {
	case 0:
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		return;
	default:
		goto resubmit;
	}

	printk("h: %d, v: %d\n", data[1], data[2]);
	

resubmit:
	status = usb_submit_urb(urb, GFP_ATOMIC);
	if (status) {
		printk(KERN_DEBUG "can not resubmit\n");
	}
}


static int usb_sample_probe(struct usb_interface *interface, const struct usb_device_id *id) {
	struct usb_device *dev = interface_to_usbdev(interface);
	
	if (dev == NULL) {
		printk(KERN_DEBUG "can not find device.\n");
		return -1;
	}

	printk(KERN_DEBUG "usb sample probe\n");
	printk(KERN_DEBUG "manufacturer: %s\n", dev->manufacturer);	
	printk(KERN_DEBUG "product: %s\n", dev->product);
	printk(KERN_DEBUG "serial: %s\n", dev->serial);
	printk(KERN_DEBUG "devpath: %s\n", dev->devpath);

	struct usb_host_interface *host_intf = interface->cur_altsetting;

	printk(KERN_DEBUG "bNumEndpoints: %d\n", host_intf->desc.bNumEndpoints);

	if (host_intf->desc.bNumEndpoints != 1) {
		printk(KERN_DEBUG "endpoints number is not 1\n");
		return -ENODEV;
	}

	struct usb_endpoint_descriptor *endpoint = &host_intf->endpoint[0].desc;

	if (!usb_endpoint_is_int_in(endpoint)) {
		printk(KERN_DEBUG "endpoints is not int\n");
		return -ENODEV;
	}

	int pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
	int maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	printk(KERN_DEBUG "maxpacket: %d\n", maxp);

	struct usb_mouse *mouse = kzalloc(sizeof(struct usb_mouse), GFP_KERNEL);
	sample_dev.mouse = mouse;

	if (mouse == NULL) {
		printk(KERN_DEBUG "can not alloc memory for usb_mouse\n");
		return -ENODEV;
	}

	mouse->irq = usb_alloc_urb(0, GFP_KERNEL);

	mouse->data = usb_buffer_alloc(dev, 8, GFP_ATOMIC, &mouse->data_dma);

	usb_fill_int_urb(mouse->irq, dev, pipe, mouse->data, (maxp > 8 ? 8 : maxp), usb_mouse_irq, mouse, endpoint->bInterval);

	usb_set_intfdata(interface, mouse);

//	struct usb_device *dev = interface_to_usbdev(interface);

	printk(KERN_DEBUG "product: %s, manufacturer: %s, serial: %s\n", dev->product, dev->manufacturer, dev->serial);

	if (usb_register_dev(interface, &usb_sample_class)) {
		printk(KERN_DEBUG "can not register device\n");
		return -1;
	}


	return 0;	
}

static void usb_sample_disconnect(struct usb_interface *interface) {
	struct usb_mouse *mouse = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	if (mouse) {
		usb_deregister_dev(interface, &usb_sample_class);
		usb_kill_urb(mouse->irq);
		usb_free_urb(mouse->irq);
		usb_buffer_free(interface_to_usbdev(interface), 8, mouse->data, mouse->data_dma);

		kfree(mouse);
	}
}

static int __init usb_sample_init(void) {
	int ret = usb_register(&usb_sample_driver);
	printk(KERN_DEBUG "usb sample init\n");

	if (ret) {
		err("usb_register failed. Error number: %d", ret);
	}

	return ret;
}

static void __exit usb_sample_exit(void) {
	usb_deregister(&usb_sample_driver);
	printk(KERN_DEBUG "usb sample exit\n");
}

module_init(usb_sample_init);
module_exit(usb_sample_exit);
