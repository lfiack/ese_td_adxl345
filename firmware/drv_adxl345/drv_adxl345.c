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

	/* À compléter */

	return 0;
}

int adxl345_start(h_adxl345_t * h_adxl345)
{
	// Write '1' to the Measure bit in POWER_CTL register

	/* À compléter */

	return 0;
}

int adxl345_data_available(h_adxl345_t * h_adxl345)
{
	return h_adxl345->data_available;
}

int adxl345_read_acceleration(h_adxl345_t * h_adxl345)
{
	// Read X, Y and Z accelerations

	/* À compléter */

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
