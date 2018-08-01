#include "mraa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

//referenced from the 'Grove Temperature Sensor'
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

unsigned int period=1000; // used for the sound sensor 

// declare the analog input contexts
mraa_aio_context temp;
mraa_aio_context light;
mraa_aio_context sound;

// initialize the contexts
void init(void){
	temp = mraa_aio_init(0);
	light = mraa_aio_init(1);
	sound = mraa_aio_init(2);
}

void measureSensors(void){
	// if the sensors are not initialized, exit with 1
	if(temp==NULL||light==NULL||sound==NULL){
			fprintf(stderr,"unable to initialize AIO");
		exit(1);
	}
	char buf[50];
	uint16_t temp_val;
	uint16_t light_val;
	uint16_t sound_val;
	float R;
	float temperature;
	float adj_temp;
	float adj_light;
	float adj_sound;
	int n;
	int index;
	while(1){
		adj_sound = 0;
		adj_temp = 0;
		adj_light = 0;
		// mreasuring data from sensors and finding average value
		for(index=0;index<1000000;index+=period){
			//measuring analog data
			sound_val = mraa_aio_read(sound);
			temp_val = mraa_aio_read(temp);
			light_val = mraa_aio_read(light);
			//recording sound
			adj_sound += sound_val;
			//recording temperature
			R = R0*(1023.0/temp_val-1.0);
			adj_temp += 1.0/(log(R/R0)/B+1/298.15)-273.15;
			//recording light
			adj_light += light_val;
			usleep(period);
		}
    adj_temp = adj_temp/(1000000/period);
		adj_light = adj_light/(1000000/period);
		adj_sound = adj_sound/(1000000/period);
		sprintf(buf, "temp:%.1f\tlight:%.1f\tsound:%.1f\n",adj_temp,adj_light,adj_sound);
		n = strlen(buf);
		write(1,buf,n);
	}
}

int main(int argv, char **argc){
	init();
	measureSensors();
}
