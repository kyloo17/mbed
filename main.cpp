/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

namespace {
#define PERIOD_MS 2000ms
DigitalOut myled(LED1);
InterruptIn bouton(BUTTON1);
uint64_t a = 0;
int b = 0;
Timer t;
}
void flip(){
	t.start();
	myled.write(1);
}

void flip2(){
	t.stop();
	a=t.read_ms();
	b=1;
}

int main()
{
	bouton.rise(flip);
	bouton.fall(flip2);
	
	while(true)	{

		if (b == 1) {
			printf("timer = %lld milliseconds\n",a);
			myled.write(0);
			b=0;
			t.reset();
		}
		ThisThread::sleep_for(PERIOD_MS / 2);
	}
		
	
}
