/*
 * ADC.h
 *
 * Created: 06-05-2021 13:56:01
 *  Author: sebas
 */ 



// converted 10 bit value in (ADCL + (ADCH<<8)), interupt: ADC_vect
#ifndef ADC_H_
#define ADC_H_

//initialize ADC in freerunning mode
void initFreeADC(char channel);

//initialize ADC with timer1 overflow as trigger
void initOverflowInt1ADC(char channel);

//initialize ADC with timer1 overflow as trigger
void initOverflowInt0ADC(char channel);

void initCTCB1ADC(char channel);



#endif /* ADC_H_ */