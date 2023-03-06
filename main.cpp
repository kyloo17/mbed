/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

namespace {
#define PERIOD_MS 2000ms
DigitalOut myled(LED1);
}

int main()
{
	while (true) {
		printf("Alive! \n");
		if (myled.read() == 0){
			myled.write(1);
		}
		else {
			myled.write(0);
		}
		ThisThread::sleep_for(PERIOD_MS / 2);
	}
}
