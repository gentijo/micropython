set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/sdkconfig.ble
)

if(MICROPY_BOARD_VARIANT STREQUAL "D2WD")
    set(SDKCONFIG_DEFAULTS
        ${SDKCONFIG_DEFAULTS}
        boards/ESP32_GENERIC/sdkconfig.d2wd
    )

    list(APPEND MICROPY_DEF_BOARD
        MICROPY_HW_MCU_NAME="ESP32-D2WD"
        # Disable some options to reduce firmware size.
        MICROPY_OPT_COMPUTED_GOTO=0
        MICROPY_PY_NETWORK_LAN=0
    )
endif()

if(MICROPY_BOARD_VARIANT STREQUAL "OTA")
    set(SDKCONFIG_DEFAULTS
        ${SDKCONFIG_DEFAULTS}
        boards/ESP32_GENERIC/sdkconfig.ota
    )

    list(APPEND MICROPY_DEF_BOARD
        MICROPY_HW_BOARD_NAME="Generic ESP32 module with OTA"
    )
endif()

if(MICROPY_BOARD_VARIANT STREQUAL "SPIRAM")
    set(SDKCONFIG_DEFAULTS
        ${SDKCONFIG_DEFAULTS}
        boards/sdkconfig.spiram
    )

    list(APPEND MICROPY_DEF_BOARD
        MICROPY_HW_BOARD_NAME="Generic ESP32 module with SPIRAM"
    )
endif()

if(MICROPY_BOARD_VARIANT STREQUAL "UNICORE")
    set(SDKCONFIG_DEFAULTS
        ${SDKCONFIG_DEFAULTS}
        boards/ESP32_GENERIC/sdkconfig.unicore
    )

    list(APPEND MICROPY_DEF_BOARD
        MICROPY_HW_MCU_NAME="ESP32-UNICORE"
    )
endif()

get_filename_component(micro_ros_component ../../../components/micro_ros_espidf_component ABSOLUTE)
get_filename_component(lvgl_component ../../../components/lvgl ABSOLUTE)
get_filename_component(gt911_touch_component ../../../components/esp-bsp/components/lcd_touch/esp_lcd_touch_gt911 ABSOLUTE)
get_filename_component(esp_lcd_component  ../../../../esp/idf/components/esp_lcd ABSOLUTE)

list(APPEND EXTRA_COMPONENT_DIRS 
#    ${micro_ros_component}
#    ${lvgl_component}
#    ${gt911_touch_component}
#    ${esp_lcd_component}
)

#list(APPEND IDF_COMPONENTS
##    esp_lcd
#)

#set (USERMOD_C_DIR
#    ../../../../modules
#    ../../../../libROSMicroPyGUI/micropython.cmake
#)

#get_filename_component(mod_ros_micropy ../../../modules/libROSMicroPy/micropython.cmake ABSOLUTE)
#include(${mod_ros_micropy})
#include(../../../modules/libROSMicroPyGUI/micropython.cmake)
