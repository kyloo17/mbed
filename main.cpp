#include "mbed.h"
#include "bme280.h"
DigitalOut myled(LED1);
Mutex stdio_mutex;
Thread thread1;
Thread thread2;
namespace {
#define PERIOD_MS 1s
int a =0;
int b =0;
}

using namespace sixtron;


static I2C i2c(I2C1_SDA, I2C1_SCL);
static BME280 bme(&i2c, BME280::I2CAddress::Address1);

void Ping_thread(){
	
	while (a<100){
		stdio_mutex.lock();
		printf("Ping\n");
		a = a+1; 	
		stdio_mutex.unlock();
	}
	
}

void Pong_thread(){
	
	while (b<100){
		stdio_mutex.lock();
		printf("Pong\n");
		b = b+1; 
		stdio_mutex.unlock();
	}
	
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

	
	
	thread1.start(Ping_thread);
	thread2.start(Pong_thread);


    while (true) {
       /* printf("\nTemperature: %.3f °C\n",  bme.temperature());
        printf(  "Pressure:    %.3f hPa\n", (bme.pressure() / 100.0f));
        printf(  "Humidity:    %.3f %%\n",  bme.humidity());*/
        wait_us(5000);
		if (myled.read() == 0){
			myled.write(1);
		}
		else {
			myled.write(0);
		}
        ThisThread::sleep_for(PERIOD_MS);
    }
}