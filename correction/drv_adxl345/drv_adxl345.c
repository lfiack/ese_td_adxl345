/*
 * drv_adxl345.c
 *
 *  Created on: 24 oct. 2022
 *      Author: laurentf
 */

#include "drv_adxl345.h"

int adxl345_init(h_adxl345_t * h_adxl345)
{
	h_adxl345->data_available = 0;
	h_adxl345->skipped_data = 0;

	uint8_t devid;
	uint8_t reg;

	// Récupérer le DEVID, et vérifier si tout est bon
	h_adxl345->serial_drv.receive(CMD_READ | CMD_SINGLEBYTE | ADDR_DEVID, &devid, 1);
	if (devid != 0xE5)
	{
		return -1;
	}
	h_adxl345->devid = devid;

	// Write '1' to the DATA_READY bit in the INT_ENABLE register
	// Generate an interrupt when a new data is ready
	reg = 0x80;
	h_adxl345->serial_drv.transmit(CMD_WRITE | CMD_SINGLEBYTE | ADDR_INT_ENABLE, &reg, 1);

	// Rate
	h_adxl345->serial_drv.receive(CMD_READ | CMD_SINGLEBYTE | ADDR_BW_RATE, &reg, 1);
	reg &= 0xF0;
	reg |= h_adxl345->rate;
	h_adxl345->serial_drv.transmit(CMD_WRITE | CMD_SINGLEBYTE | ADDR_BW_RATE, &reg, 1);

	// Range
	h_adxl345->serial_drv.receive(CMD_READ | CMD_SINGLEBYTE | ADDR_DATA_FORMAT, &reg, 1);
	reg &= 0xFC;
	reg |= h_adxl345->range;
	h_adxl345->serial_drv.transmit(CMD_WRITE | CMD_SINGLEBYTE | ADDR_DATA_FORMAT, &reg, 1);

	return 0;
}

int adxl345_start(h_adxl345_t * h_adxl345)
{
	// Write '1' to the Measure bit in POWER_CTL register
	uint8_t reg = 0x08;
	h_adxl345->serial_drv.transmit(CMD_WRITE | CMD_SINGLEBYTE | ADDR_POWER_CTL, &reg, 1);

	return 0;
}

int adxl345_data_available(h_adxl345_t * h_adxl345)
{
	return h_adxl345->data_available;
}

int adxl345_read_acceleration(h_adxl345_t * h_adxl345)
{
	uint8_t buffer[6];

	// Read X, Y and Z accelerations
	h_adxl345->serial_drv.receive(CMD_READ | CMD_MULTIBYTE | ADDR_DATA_X0, buffer, 6);
	h_adxl345->data_available = 0;

	int16_t x_int = buffer[0] + (buffer[1] << 8);
	int16_t y_int = buffer[2] + (buffer[3] << 8);
	int16_t z_int = buffer[4] + (buffer[5] << 8);

	h_adxl345->x = (float) (x_int) / 256.0;
	h_adxl345->y = (float) (y_int) / 256.0;
	h_adxl345->z = (float) (z_int) / 256.0;

	return 0;
}

float adxl345_get_x_acceleration(h_adxl345_t * h_adxl345)
{
	return h_adxl345->x;
}

float adxl345_get_y_acceleration(h_adxl345_t * h_adxl345)
{
	return h_adxl345->y;
}

float adxl345_get_z_acceleration(h_adxl345_t * h_adxl345)
{
	return h_adxl345->z;
}

void adxl345_irq_cb(h_adxl345_t * h_adxl345)
{
	if (h_adxl345->data_available)
	{
		h_adxl345->skipped_data++;
	}
	else
	{
		h_adxl345->data_available = 1;
	}
}
