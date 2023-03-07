#include "mbed.h"
#include "bme280.h"
DigitalOut myled(LED1);
Mutex stdio_mutex;
Thread thread1;

InterruptIn bouton(BUTTON1);

EventQueue queue;
namespace {
#define PERIOD_MS 1s

}

using namespace sixtron;


static I2C i2c(I2C1_SDA, I2C1_SCL);
static BME280 bme(&i2c, BME280::I2CAddress::Address1);

void HumTemp(){
	printf(  "Humidity:    %.3f %%\n",  bme.humidity());
	printf("\nTemperature: %.3f °C\n",  bme.temperature());
	}
	


void Press(){
	printf(  "Pressure:    %.3f hPa\n", (bme.pressure() / 100.0f));
}

void Led(){
	if (myled.read() == 0){
			myled.write(1);
	}
	else {
			myled.write(0);
	}
}

void boutonInterrupt(){
	queue.call(Press);

}

int main()
{
    if (!bme.initialize()) {
        printf("Couldn't initialize the BME280...\n");
        return -1;
    }

    bme.set_sampling(BME280::SensorMode::NORMAL,
                     BME280::SensorSampling::OVERSAMPLING_X1,
                     BME280::SensorSampling::OVERSAMPLING_X1,
                     BME280::SensorSampling::OVERSAMPLING_X1,
                     BME280::SensorFilter::OFF,
                     BME280::StandbyDuration::MS_1000);

	
	thread1.start(callback(&queue, &EventQueue::dispatch_forever));
	queue.call_every(2000ms, HumTemp);
	queue.call_every(5000ms, Led);
	
	bouton.rise(boutonInterrupt);

    while (true) {
       
       
        wait_us(5000);
		
        ThisThread::sleep_for(PERIOD_MS);
    }
}