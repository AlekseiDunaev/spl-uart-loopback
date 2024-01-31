#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm8s.h"

// #define F_CPU 16000000UL
#define dly_const (F_CPU / 16000000.0F)

void delay_us(uint16_t value);
void delay_ms(uint16_t value);

#endif