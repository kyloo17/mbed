/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
I2C i2c(I2C1_SDA, I2C1_SCL);

namespace {
#define PERIOD_MS 2000ms
}
const int addr8bit = 0x18 << 1;



int main()
{
	
	char data[2];
	while(true)	{

		data[0] = 0x08;
		i2c.write(addr8bit, data, 1);
		i2c.read(addr8bit, data, 1);

		printf("Temp = %f\n", float(data[0])/2.+23);

	
		ThisThread::sleep_for(PERIOD_MS / 2);
	}
		
	
}
