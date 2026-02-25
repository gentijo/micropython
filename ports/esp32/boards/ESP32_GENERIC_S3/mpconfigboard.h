#ifndef MICROPY_HW_BOARD_NAME
// Can be set by mpconfigboard.cmake.
#define MICROPY_HW_BOARD_NAME               "Generic ESP32S3 module"
#endif
#define MICROPY_HW_MCU_NAME                 "ESP32S3"

// Enable UART REPL for modules that have an external USB-UART and don't use native USB.
#define MICROPY_HW_ENABLE_UART_REPL         (1)

#define MICROPY_HW_I2C0_SCL                 (9)
#define MICROPY_HW_I2C0_SDA                 (8)
#define MICROPY_HW_ENABLE_USBDEV            (1)
#define MICROPY_HW_ESP_USB_SERIAL_JTAG      (0)

// Enable TinyUSB CDC-ECM network class for usbnet external module.
#define MICROPY_HW_USB_NET                  (1)
#define MICROPY_HW_USB_NET_INTERFACE_STRING "Board NET"
#define MICROPY_HW_USB_NET_MAC_STRING       "020000000001"
// Prefer CDC-NCM on Linux hosts; ECM can stall after first ARP exchange.
#define CFG_TUD_ECM_RNDIS                   (0)
#define CFG_TUD_NCM                         (1)
