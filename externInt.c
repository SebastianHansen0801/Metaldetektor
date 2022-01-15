/*
 * externInt.c
 *
 * Created: 25-03-2021 15:30:57
 * Author : sebas
 */ 

#include <avr/io.h>


void enable_int2() {
	EIMSK |= (1 << INT2);
	PORTD |= 0x04;
}

void disable_int2() {
	EIMSK &=~ (1 << INT2);
	PORTD %=~ 0x04;
}

void enable_int4() {
	EIMSK |= (1 << INT4);
	PORTE |= 0x10;
}

void disable_int4() {
	EIMSK &=~ (1 << INT4);
	PORTE &=~ 0x10;
}

void enable_int5() {
	EIMSK |= (1 << INT5);
	PORTE |= 0x20;
}

void disable_int5() {
	EIMSK &=~ (1 << INT5);
	PORTE &= 0x20;
}

