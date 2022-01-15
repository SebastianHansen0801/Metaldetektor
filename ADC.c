/*
 * ADC.c
 *
 * Created: 06-05-2021 13:54:36
 *  Author: sebas
 */ 

#include <avr/io.h>

//initialize ADC in freerunning mode
void initFreeADC(char channel) {
	ADMUX = channel;
	ADMUX|=(1<<REFS0); //internal 5v ref
	ADCSRA|=(1<<ADEN)|(1<<ADATE)|(1<<ADIE); //enable adc, enable autotrigger, enable interupt, start sample;
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //prescaling to get 125kH clock freq
	ADCSRA|=(1<<ADSC); //start sampling
	DIDR0 = (1<<channel); //turning of the digital outputbuffers on all other channels
	DIDR0 =~ DIDR0;
	DIDR2 =0xff;
}

//initialize ADC with timer1 overflow as trigger
void initOverflowInt1ADC(char channel) {
	ADMUX = channel;
	ADMUX|=(1<<REFS0); //internal 5v ref
	ADCSRA|=(1<<ADEN)|(1<<ADATE)|(1<<ADIE); //enable adc, enable autotrigger, enable interupt, start sample;
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //prescaling to get 125kH clock freq
	ADCSRB|=(1<<ADTS2)|(1<<ADTS1); //setting timer 1 overflow as trigger
	DIDR0 = (1<<channel); //turning of the digital outputbuffers on all other channels
	DIDR0 =~ DIDR0;
	DIDR2 =0xff;
}

//initialize ADC with timer0 overflow as trigger
void initOverflowInt0ADC(char channel) {
	ADMUX = channel;
	ADMUX|=(1<<REFS0); //internal 5v ref
	ADCSRA|=(1<<ADEN)|(1<<ADATE)|(1<<ADIE); //enable adc, enable autotrigger, enable interupt, start sample;
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //prescaling to get 125kH clock freq
	ADCSRB|=(1<<ADTS2); //setting timer 1 overflow as trigger
	DIDR0 = (1<<channel); //turning of the digital outputbuffers on all other channels
	DIDR0 =~ DIDR0;
	DIDR2 =0xff;
}

//initialize ADC with timer1 comp b as trigger
void initCTCB1(char channel) {
	ADMUX = channel;
	ADMUX|=(1<<REFS0); //internal 5v ref
	ADCSRA|=(1<<ADEN)|(1<<ADATE)|(1<<ADIE); //enable adc, enable autotrigger, enable interupt, start sample;
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //prescaling to get 125kH clock freq
	ADCSRB|=(1<<ADTS2)|(1<<ADTS0); //setting timer 1 comp b as trigger
	DIDR0 = (1<<channel); //turning of the digital outputbuffers on all other channels
	DIDR0 =~ DIDR0;
	DIDR2 =0xff;
}