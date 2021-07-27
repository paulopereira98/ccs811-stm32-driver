/*
	Driver for the ccs811 sensor for stm32.
	Copyright (C) 2019  Paulo Pereira	(EEIC-UMinho)
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file ccs811.h
 * @brief Driver for the ccs811 sensor for stm32.
 */

#ifndef _CCS811_H_
#define _CCS811_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "stdint.h"

#define CCS811_I2C_ADDR 0x5A
#define CCS811_I2C_HANDLER hi2c2

//I2C REGISTERS				//accessible on:
#define STATUS 			0x00	//APPLICATION & BOOTLOADER
#define MEAS_MODE 		0x01	//APPLICATION ONLY
#define ALG_RESULT_DATA 	0x02	//APPLICATION ONLY
#define RAW_DATA 		0x03	//APPLICATION ONLY
#define ENV_DATA 		0x05	//APPLICATION ONLY
#define NTC 			0x06	//APPLICATION ONLY
#define THRESHOLDS 		0x10	//APPLICATION ONLY
#define BASELINE 		0x11	//APPLICATION ONLY
#define HW_ID 			0x20	//APPLICATION & BOOTLOADER
#define HW_VERSION 		0x21	//APPLICATION & BOOTLOADER
#define FW_BOOT_VERSION 	0x23 	//APPLICATION & BOOTLOADER
#define FW_APP_VERSION 		0x24	//APPLICATION & BOOTLOADER
#define ERROR_ID 		0xE0	//APPLICATION & BOOTLOADER
#define APP_ERASE 		0xF1	//BOOTLOADER ONLY
#define APP_DATA 		0xF2	//BOOTLOADER ONLY
#define APP_VERIFY 		0xF3	//BOOTLOADER ONLY
#define APP_START 		0xF4	//BOOTLOADER ONLY
#define SW_RESET 		0xFF	//APPLICATION & BOOTLOADER

//STATUS Register
#define FW_MODE(X)		((X & 0x1) << 7)
#define FW_MODE_BOOT	0x0	//Allows new firmware to be loaded
#define FW_MODE_APPL	0x1	//CCS811 is ready to take ADC measurements
#define APP_VALID(X)	((X & 0x1) << 4)
#define APP_VALID_NOAPP	0x0	//No application firmware loaded
#define APP_VALID_VALID 0x1	//Valid application firmware loaded
#define DATA_READY(X) 	((X & 0x1) << 3)
#define DATA_READY_NO 	0x0	//No new data samples are ready
#define DATA_READY_NEW 	0x1	//A new data sample is ready in ALG_RESULT_DATA, this bit is cleared when ALG_RESULT_DATA is read on the I2C interface
#define ERROR 0x00

//MEAS_MODE Register
#define DRIVE_MODE(X) ((X & 0x7) << 4)
#define DRIVE_MODE_MODE0 0x0 //Idle (Measurements are disabled in this mode) 001
#define DRIVE_MODE_MODE1 0x1 //Constant power mode, IAQ measurement every second 010
#define DRIVE_MODE_MODE2 0x2 //Pulse heating mode IAQ measurement every 10 seconds 011
#define DRIVE_MODE_MODE3 0x3 //Low power pulse heating mode IAQ measurement every 60 seconds 100
#define DRIVE_MODE_MODE4 0x4 //Constant power mode, sensor measurement every 250ms
#define INT_DATARDY 0x03
#define INT_THRESH 0x02

	void ccs811_init(void);
	uint32_t ccs811_measureCO2(void);
	uint32_t ccs811_measureTVOC(void);
	void ccs811_measure_CO2_TVOC(uint32_t *co2, uint32_t *tvoc);
	void ccs811_temp_rh_compensation(float, float);

#ifdef __cplusplus
}
#endif

#endif /* _CCS811_H_ */
