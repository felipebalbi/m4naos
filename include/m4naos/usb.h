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

#ifndef __M4NAOS_USB_H
#define __M4NAOS_USB_H

#include <m4naos/list.h>

struct usb_ep;
struct usb_ops;

struct usb_hw {
	struct usb_ops *ops;
	struct list_head *eps;
};

struct usb_ctrl_req {
};

struct usb_ep_ops {
	int (*enable)(struct usb_ep *ep);
	void (*disable)(struct usb_ep *ep);

	struct usb_request *(*alloc_request)(struct usb_ep *ep);
	void (*free_request)(struct usb_ep *ep);

	int (*queue)(struct usb_ep *ep, struct usb_request *req);
	int (*dequeue)(struct usb_ep *ep, struct usb_request *req);

	int (*set_halt)(struct usb_ep *ep, int value);
	int (*set_wedge)(struct usb_ep *ep, int value);
};

struct usb_ep {
	void			*drvdata;
	const char		*name;
	const struct usb_ep_ops	*ops;
	u8			num;
};

struct usb_ops {
	int (*start)(struct usb_hw *hw);
	void (*stop)(struct usb_hw *hw);
	int (*reset)(struct usb_hw *hw);
	int (*setup)(struct usb_hw *hw, struct usb_ctrl_req *ctrl);
};

int register_usb(struct usb_hw *hw);

#endif /* __M4NAOS_USB_H */
