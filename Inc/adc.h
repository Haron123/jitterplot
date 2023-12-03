#ifndef __ADC_H
#define __ADC_H

// For the atmega, adc0 to adc8 mux bits correspond to the number, for example adc3 mux bits are 0b0011

#include <avr/io.h>

/**
  * @brief sets up the adc on the ATMEGA328P
  * Uses VCC as voltage reference
  */
void setup_adc();

/**
  * @brief returns the value of the
  * ADC for a given MUX
  * @param mux the mux to be probed
  */
uint16_t get_adc(uint8_t mux);

#endif
