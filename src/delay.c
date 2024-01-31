#include "delay.h"

void delay_us(uint16_t value) {
  register unsigned int loops = (dly_const * value) ;

  while(loops) {
    __asm__ ("nop");
    loops--;
  };
}

void delay_ms(uint16_t value) {
  while(value)
    {
      delay_us(1000);
      value--;
    };
}