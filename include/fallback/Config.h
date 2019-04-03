/* Copyright (C) 2019 Lee C. Bussy (@LBussy)

This file is part of LBussy's BrewPi Firmware Remix (BrewPi-Firmware-RMX).

BrewPi Firmware RMX is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

BrewPi Firmware RMX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with BrewPi Firmware RMX. If not, see <https://www.gnu.org/licenses/>.

These scripts were originally a part of firmware, a part of
the BrewPi project. Legacy support (for the very popular Arduino
controller) seems to have been discontinued in favor of new hardware.

All credit for the original firmware goes to @elcojacobs,
@m-mcgowan, @elnicoCZ, @ntfreak, @Gargy007 and I'm sure many more
contributors around the world. My apologies if I have missed anyone;
those were the names listed as contributors on the Legacy branch.

See: 'original-license.md' for notes about the original project's
license and credits. */

#pragma once

//////////////////////////////////////////////////////////////////////////
///                   !!! DO NOT EDIT THIS FILE DIRECTLY !!!           ///
///                   !!! DO NOT EDIT THIS FILE DIRECTLY !!!           ///
///                   !!! DO NOT EDIT THIS FILE DIRECTLY !!!           ///
//////////////////////////////////////////////////////////////////////////
///
/// Instead, copy the file from
///
///             include/fallback/Config.h
/// to
///             include/Config.h
///
/// (i.e. up one directory.)
///
/// Then remove this comment, and uncomment out the configuration values
/// you'd like to re-define.
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define build name
//
// #ifndef BUILD_NAME
// #define BUILD_NAME PIO_SRC_REV
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set verbosity of debug messages 0-3
// 0: means no debug messages
// 1: is typical debug messages required for end users
// 2-3: more verbose debug messages
//
// #ifndef BREWPI_DEBUG
// #define BREWPI_DEBUG 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define which brewpi shield is used.
// BREWPI_SHIELD_REV_A The RevA shield (ca. Feb 2013), two OneWire buses,
//                     door, heat, cool.
// BREWPI_SHIELD_REV_C The RevC shield (ca. May 2013). One common OneWire bus,
//                     4 actuators. Dynaconfig.
// BREWPI_SHIELD_DIY "Classic" DIY Shield with neither LCD, buzzer, nor rotary
//                     encoder.
//
// #ifndef BREWPI_STATIC_CONFIG
// #define BREWPI_STATIC_CONFIG BREWPI_SHIELD_REV_A
// #define BREWPI_STATIC_CONFIG BREWPI_SHIELD_REV_C
// #define BREWPI_STATIC_CONFIG BREWPI_SHIELD_DIY
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set the display type
//
// #define BREWPI_LCD_TYPE BREWPI_DISPLAY_NONE
// #define BREWPI_LCD_TYPE BREWPI_DISPLAY_CLASSIC
// #define BREWPI_LCD_TYPE BREWPI_DISPLAY_SHIFT_LCD
// #define BREWPI_LCD_TYPE BREWPI_DISPLAY_OLED
// #define BREWPI_LCD_TYPE BREWPI_DISPLAY_TWI_LCD
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set TWI/I2C LCD parameters
// See: https://www.arduino.cc/en/Reference/PortManipulation
//
// #define TWI_ADDRESS		0x27
// #define SDA_PIN			2
// #define SDA_PORT		    PORTB
// #define SCL_PIN			3
// #define SCL_PORT		    PORTB
// #define I2C_FASTMODE	    1
// #define I2C_NOINTERRUPT	1
// #define I2C_TIMEOUT		500
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Enable the simulator. Real sensors/actuators are replaced with simulated
// versions. In particular, the values reported by temp sensors are based on
// a model of the fridge/beer.
//
// #ifndef BREWPI_SIMULATE
// #define BREWPI_SIMULATE 0
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Enable DS2413 Actuators.
//
// #ifndef BREWPI_DS2413
// #define BREWPI_DS2413 0
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// This flag virtualizes as much of the hardware as possible, so the code can
// be run in the AvrStudio simulator, which only emulates the microcontroller,
// not any attached peripherals.
//
// #ifndef BREWPI_EMULATE
// #define BREWPI_EMULATE 0
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Flag to control use of cascaded filter
//
// #ifndef TEMP_SENSOR_CASCADED_FILTER
// #define TEMP_SENSOR_CASCADED_FILTER 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Flag to control implementation of TempControl as a static class.
// Should normally be left alone unles you are experimenting with multi-
// instancing.
//
// #ifndef TEMP_CONTROL_STATIC
// #define TEMP_CONTROL_STATIC 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Flag to control use of Fast digital pin functions
//
// #ifndef FAST_DIGITAL_PIN
// #define FAST_DIGITAL_PIN 0
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Enable the LCD menu.
//
// #ifndef BREWPI_MENU
// #define BREWPI_MENU 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// #ifndef BREWPI_BUZZER
// #define BREWPI_BUZZER 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// #ifndef BREWPI_ROTARY_ENCODER
// #define BREWPI_ROTARY_ENCODER 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// #ifndef BREWPI_EEPROM_HELPER_COMMANDS
// #define BREWPI_EEPROM_HELPER_COMMANDS BREWPI_DEBUG || BREWPI_SIMULATE
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// BREWPI_SENSOR_PINS - can be disabled if only using onewire devices
//
// #ifndef BREWPI_SENSOR_PINS
// #define BREWPI_SENSOR_PINS 1
// #endif
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// BREWPI_ACTUATOR_PINS - can be disabled if only using onewire devices
// #ifndef BREWPI_ACTUATOR_PINS
// #define BREWPI_ACTUATOR_PINS 1
// #endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// FORCE_DEVICE_DEFAULTS - Overwrite the chamber/beer number to prevent user
//                         error.
//
// #ifndef FORCE_DEVICE_DEFAULTS
// #define FORCE_DEVICE_DEFAULTS 1
// #endif
//
//////////////////////////////////////////////////////////////////////////
