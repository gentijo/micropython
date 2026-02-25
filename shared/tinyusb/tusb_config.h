/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020-2021 Damien P. George
 * Copyright (c) 2022 Angus Gratton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef MICROPY_INCLUDED_SHARED_TINYUSB_TUSB_CONFIG_H
#define MICROPY_INCLUDED_SHARED_TINYUSB_TUSB_CONFIG_H

#include "py/mpconfig.h"

#if MICROPY_HW_ENABLE_USBDEV

#ifndef MICROPY_HW_ENABLE_USB_RUNTIME_DEVICE
#define MICROPY_HW_ENABLE_USB_RUNTIME_DEVICE 0
#endif

#ifndef MICROPY_HW_USB_MANUFACTURER_STRING
#define MICROPY_HW_USB_MANUFACTURER_STRING "MicroPython"
#endif

#ifndef MICROPY_HW_USB_PRODUCT_FS_STRING
#define MICROPY_HW_USB_PRODUCT_FS_STRING "Board in FS mode"
#endif

#ifndef MICROPY_HW_USB_CDC_INTERFACE_STRING
#define MICROPY_HW_USB_CDC_INTERFACE_STRING "Board CDC"
#endif

#ifndef MICROPY_HW_USB_MSC_INQUIRY_VENDOR_STRING
#define MICROPY_HW_USB_MSC_INQUIRY_VENDOR_STRING "MicroPy"
#endif

#ifndef MICROPY_HW_USB_MSC_INQUIRY_PRODUCT_STRING
#define MICROPY_HW_USB_MSC_INQUIRY_PRODUCT_STRING "Mass Storage"
#endif

#ifndef MICROPY_HW_USB_MSC_INQUIRY_REVISION_STRING
#define MICROPY_HW_USB_MSC_INQUIRY_REVISION_STRING "1.00"
#endif

#if !defined(CFG_TUSB_RHPORT0_MODE) && !defined(CFG_TUSB_RHPORT1_MODE)
#define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_DEVICE)
#endif

#if MICROPY_HW_USB_CDC
#define CFG_TUD_CDC             (1)
#else
#define CFG_TUD_CDC             (0)
#endif

#if MICROPY_HW_USB_MSC
#define CFG_TUD_MSC             (1)
#else
#define CFG_TUD_MSC             (0)
#endif

#ifndef MICROPY_HW_USB_NET
#define MICROPY_HW_USB_NET      (0)
#endif

// TinyUSB NET class enablement (ECM/RNDIS or NCM).
#ifndef CFG_TUD_ECM_RNDIS
#if MICROPY_HW_USB_NET
#define CFG_TUD_ECM_RNDIS       (1)
#else
#define CFG_TUD_ECM_RNDIS       (0)
#endif
#endif

#ifndef CFG_TUD_NCM
#define CFG_TUD_NCM             (0)
#endif

// CDC Configuration
#if CFG_TUD_CDC
#ifndef CFG_TUD_CDC_RX_BUFSIZE
#define CFG_TUD_CDC_RX_BUFSIZE  ((CFG_TUD_MAX_SPEED == OPT_MODE_HIGH_SPEED) ? 512 : 256)
#endif
#ifndef CFG_TUD_CDC_TX_BUFSIZE
#define CFG_TUD_CDC_TX_BUFSIZE  ((CFG_TUD_MAX_SPEED == OPT_MODE_HIGH_SPEED) ? 512 : 256)
#endif
#endif // CFG_TUD_CDC

// MSC Configuration
#if CFG_TUD_MSC
#ifndef MICROPY_HW_USB_MSC_INTERFACE_STRING
#define MICROPY_HW_USB_MSC_INTERFACE_STRING "Board MSC"
#endif
// Set MSC EP buffer size to FatFS block size to avoid partial read/writes (offset arg).
#define CFG_TUD_MSC_BUFSIZE (MICROPY_FATFS_MAX_SS)
#endif // CFG_TUD_MSC

#if CFG_TUD_ECM_RNDIS || CFG_TUD_NCM
#ifndef MICROPY_HW_USB_NET_INTERFACE_STRING
#define MICROPY_HW_USB_NET_INTERFACE_STRING "Board NET"
#endif
#ifndef MICROPY_HW_USB_NET_MAC_STRING
#define MICROPY_HW_USB_NET_MAC_STRING "020000000001"
#endif
#endif // CFG_TUD_ECM_RNDIS || CFG_TUD_NCM

// Define built-in interface, string and endpoint numbering based on the above config

#define USBD_STR_0 (0x00)
#define USBD_STR_MANUF (0x01)
#define USBD_STR_PRODUCT (0x02)
#define USBD_STR_SERIAL (0x03)
#define USBD_STR_CDC (0x04)
#define USBD_STR_MSC (0x05)
#define USBD_STR_NET (0x06)
#define USBD_STR_NET_MAC (0x07)

#define USBD_MAX_POWER_MA (250)

#ifndef MICROPY_HW_USB_DESC_STR_MAX
#define MICROPY_HW_USB_DESC_STR_MAX (40)
#endif

#if CFG_TUD_CDC
#define USBD_ITF_CDC (0) // needs 2 interfaces
#define USBD_CDC_EP_CMD (0x81)
#define USBD_CDC_EP_OUT (0x02)
#define USBD_CDC_EP_IN (0x82)
#define USBD_ITF_AFTER_CDC (USBD_ITF_CDC + 2)
#define USBD_EP_NUM_AFTER_CDC (3)
#define USBD_STR_AFTER_CDC (USBD_STR_CDC + 1)
#else
#define USBD_ITF_AFTER_CDC (0)
#define USBD_EP_NUM_AFTER_CDC (1)
#define USBD_STR_AFTER_CDC (USBD_STR_SERIAL + 1)
#endif // CFG_TUD_CDC

#if CFG_TUD_MSC
// Interface & Endpoint numbers for MSC come after CDC, if it is enabled
#define USBD_ITF_MSC (USBD_ITF_AFTER_CDC)
#define EPNUM_MSC_OUT (USBD_EP_NUM_AFTER_CDC)
#define EPNUM_MSC_IN (0x80 | USBD_EP_NUM_AFTER_CDC)
#define USBD_ITF_AFTER_MSC (USBD_ITF_MSC + 1)
#define USBD_EP_NUM_AFTER_MSC (USBD_EP_NUM_AFTER_CDC + 1)
#define USBD_STR_AFTER_MSC (USBD_STR_MSC + 1)
#else
#define USBD_ITF_AFTER_MSC (USBD_ITF_AFTER_CDC)
#define USBD_EP_NUM_AFTER_MSC (USBD_EP_NUM_AFTER_CDC)
#define USBD_STR_AFTER_MSC (USBD_STR_AFTER_CDC)
#endif // CFG_TUD_MSC

#if CFG_TUD_ECM_RNDIS || CFG_TUD_NCM
// NET uses two interfaces: control + data.
#define USBD_ITF_NET (USBD_ITF_AFTER_MSC)
#define EPNUM_NET_OUT (USBD_EP_NUM_AFTER_MSC)
#define EPNUM_NET_IN (0x80 | USBD_EP_NUM_AFTER_MSC)
#define EPNUM_NET_NOTIF (0x80 | (USBD_EP_NUM_AFTER_MSC + 1))
#define USBD_ITF_AFTER_NET (USBD_ITF_NET + 2)
#define USBD_EP_NUM_AFTER_NET (USBD_EP_NUM_AFTER_MSC + 2)
#define USBD_STR_AFTER_NET (USBD_STR_NET_MAC + 1)
#endif // CFG_TUD_ECM_RNDIS || CFG_TUD_NCM

/* Limits of builtin USB interfaces, endpoints, strings */
#if CFG_TUD_ECM_RNDIS || CFG_TUD_NCM
#define USBD_ITF_BUILTIN_MAX (USBD_ITF_AFTER_NET)
#define USBD_STR_BUILTIN_MAX (USBD_STR_AFTER_NET)
#define USBD_EP_BUILTIN_MAX (USBD_EP_NUM_AFTER_NET)
#elif CFG_TUD_MSC
#define USBD_ITF_BUILTIN_MAX (USBD_ITF_AFTER_MSC)
#define USBD_STR_BUILTIN_MAX (USBD_STR_AFTER_MSC)
#define USBD_EP_BUILTIN_MAX (USBD_EP_NUM_AFTER_MSC)
#elif CFG_TUD_CDC
#define USBD_ITF_BUILTIN_MAX (USBD_ITF_AFTER_CDC)
#define USBD_STR_BUILTIN_MAX (USBD_STR_AFTER_CDC)
#define USBD_EP_BUILTIN_MAX (USBD_EP_NUM_AFTER_CDC)
#else // !CFG_TUD_MSC && !CFG_TUD_CDC
#define USBD_ITF_BUILTIN_MAX (0)
#define USBD_STR_BUILTIN_MAX (0)
#define USBD_EP_BUILTIN_MAX (0)
#endif

#endif // MICROPY_HW_ENABLE_USBDEV

#endif // MICROPY_INCLUDED_SHARED_TINYUSB_TUSB_CONFIG_H
