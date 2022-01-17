/*
* main.c
*
* Created: 1/5/2022 1:36:25 PM
*  Author: Sebastian Oliver Hansen (s205044)
*/

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ADC.h"
#include "timer.h"
#include "ssd1306.h"
#include "I2C.h"

#define numberOfSamples 64

void init();
void showValues(double value,char selector);
double * fourier(int * arr);

int samples[numberOfSamples] = {'\0'};
volatile char state;

enum state {idle, sampling, dft};

int main(void) {
	char ampText[5] = "Amp:";
	char phaseText[7] = "Phase:";
	double accAmp = 0;
	double accPhase = 0;
	
	init();
	
	sendStrXY(ampText,0,0);
	sendStrXY(phaseText,1,0);
	
	while(1) {
		if(state == dft) {
			accAmp = 0.9*accAmp+0.1*fourier(samples)[0];
			accPhase = 0.9*accPhase+0.1*fourier(samples)[1];
			
			showValues(accAmp,0);
			showValues(accPhase,1);
			state = idle;
		}
	}
}

ISR(TIMER1_COMPB_vect) {
	static char sigCounter = 0;
	if (sigCounter == 4) {
		PORTB^=(1<<PB6);
		sigCounter = 0;
		if(state == idle) state = sampling;
	}
	sigCounter++;
}

ISR(ADC_vect) {
	static int sampleIndex = 0;
	if(state == sampling) {
		int ADCval = 0;
		ADCval = ADCL + (ADCH<<8);
		samples[sampleIndex] = ADCval;
		sampleIndex++;
		if(sampleIndex == numberOfSamples) {
			sampleIndex = 0;
			state  = dft;
		}
	}
}

// function to initialize timer, ADC, display and I/O
void init() {
	initTimer1CTC(124,8);
	initCTCB1ADC(0);
	DDRB|=(1<<DDB6);
	PORTB|=(1<<PB6);
	
	_i2c_address = 0X78; // write address for i2c interface
	I2C_Init();  //initialize i2c interface to display
	InitializeDisplay(); //initialize  display
	clear_display();
	dim(true);
	
	sei();
}

// function do display the calculated values on the display
void showValues(double value,char selector) {
	char buffer[10] = {'\0'};
	dtostrf(value,5,1,buffer);
	sendStrXY(buffer,selector,7);
}

// function to calculate the amp and phase
double * fourier(int * arr) {
	char cosValues[5] = {1,0,-1,0};
	char sinValues[5] = {0,1,0,-1};
	int i = 0;
	double amp = 0;
	double phase = 0;
	double realPart = 0;
	double imaginaryPart = 0;
	static double result[3] = {'\0'};
	for(int n=0; n<numberOfSamples; n++) {
		realPart += samples[n]*cosValues[i];
		imaginaryPart -= samples[n]*sinValues[i];
		i++;
		if(i == 4) i = 0;
	}
	realPart = (realPart*5)/1024;
	imaginaryPart = (imaginaryPart*5)/1024;
	amp = sqrt(realPart*realPart+imaginaryPart*imaginaryPart);
	phase = atan2(imaginaryPart,realPart)*180/M_PI;
	amp = amp/(numberOfSamples/2);
	result[0] = amp;
	result[1] = phase;
	
	return result;
}