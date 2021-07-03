/* SPDX-License-Identifier: GPL-3.0-or-later */

/*
 * This file is part of M4naos
 *
 * M4naos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * M4naos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with M4naos.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __M4NAOS_USB_CH9_H
#define __M4NAOS_USB_CH9_H

#include <m4naos/kernel.h>
#include <m4naos/types.h>

#define USB20				0x0200
#define USB21				0x0210
#define USB30				0x0300
#define USB31				0x0310
#define USB32				0x0320

#define USB_DIR_IN			BIT(7)
#define USB_DIR_OUT			0

#define USB_CONFIG_ATTR_SELF_POWERED	BIT(6)
#define USB_CONFIG_ATTR_REMOTE_WAKEUP	BIT(5)

#define USB_EP_TYPE_MASK		(3 << 0)
#define USB_EP_TYPE_CTRL		(0 << 0)
#define USB_EP_TYPE_ISOC		(1 << 0)
#define USB_EP_TYPE_BULK		(2 << 0)
#define USB_EP_TYPE_INT			(3 << 0)

#define USB_EP_SYNC_TYPE_MASK		(3 << 2)
#define USB_EP_SYNC_TYPE_NONE		(0 << 2)
#define USB_EP_SYNC_TYPE_ASYNC		(1 << 2)
#define USB_EP_SYNC_TYPE_ADAPTIVE	(2 << 2)
#define USB_EP_SYNC_TYPE_SYNC		(3 << 2)

#define USB_EP_USAGE_TYPE_MASK		(3 << 4)
#define USB_EP_USAGE_TYPE_DATA		(0 << 4)
#define USB_EP_USAGE_TYPE_FEEDBACK	(1 << 4)
#define USB_EP_USAGE_TYPE_IMPLICIT	(2 << 4)

#define USB_EP_MULT_MASK		(3 << 11)
#define USB_EP_MULT_NONE		(0 << 11)
#define USB_EP_MULT_ONE			(1 << 11)
#define USB_EP_MULT_TWO			(2 << 11)

struct usb_descriptor_header {
	__u8	bLength;
	__u8	bDescriptorType;
} __packed;

struct usb_device_desc {
	__u8	bLength;
	__u8	bDescriptorType;

	__le16	bcdUSB;
	__u8	bDeviceClass;
	__u8	bDeviceSubClass;
	__u8	bDeviceProtocol;
	__u8	bMaxPacketSize0;
	__le16	idVendor;
	__le16	idProduct;
	__le16	bcdDevice;
	__u8	iManufacturer;
	__u8	iProduct;
	__u8	iSerialNumber;
	__u8	bNumConfigurations;
} __packed;

struct usb_device_qualifier {
	__u8	bLength;
	__u8	bDescriptorType;

	__le16	bcdUSB;
	__u8	bDeviceClass;
	__u8	bDeviceSubClass;
	__u8	bDeviceProtocol;
	__u8	bMaxPacketSize0;
	__u8	bNumberConfigurations;
	__u8	bReserved;
} __packed;

struct usb_config_desc {
	__u8	bLength;
	__u8	bDescriptorType;

	__le16	wTotalLength;
	__u8	bNumInterfaces;
	__u8	bConfigurationValue;
	__u8	iConfiguration;
	__u8	bmAttributes;
	__u8	bMaxPower;
} __packed;

struct usb_other_speed_config {
	__u8	bLength;
	__u8	bDescriptorType;

	__le16	wTotalLength;
	__u8	bNumInterfaces;
	__u8	bConfigurationValue;
	__u8	iConfiguration;
	__u8	bmAttributes;
	__u8	bMaxPower;
} __packed;

struct usb_interface_desc {
	__u8	bLength;
	__u8	bDescriptorType;

	__u8	bInterfaceNumber;
	__u8	bAlternateSetting;
	__u8	bNumEndpoints;
	__u8	bInterfaceClass;
	__u8	bInterfaceSubClass;
	__u8	bInterfaceProtocol;
	__u8	iInterface;
} __packed;

struct usb_endpoint_desc {
	__u8	bLength;
	__u8	bDescriptorType;

	__u8	bEndpointAddress;
	__u8	bmAttributes;
	__le16	wMaxPacketSize;
	__u8	bInterval;
} __packed;

struct usb_string_desc {
	__u8	bLength;
	__u8	bDescriptorType;

	__le16	wLANGID[0];
} __packed;

struct usb_unicode_string_desc {
	__u8	bLength;
	__u8	bDescriptorType;

	__u8	bString[0];
};

#endif /* __M4NAOS_USB_CH9_H */
