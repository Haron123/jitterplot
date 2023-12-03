#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>
#include <stdint.h>

#define gpio_pin PIND

#define LEFT PB4
#define DOWN PB5
#define UP PB6
#define RIGHT PB7

/**
 * @brief gives you the logical level of a button,
 * @param button the pin of the button on the port
 * @retval ==0 means not pressed, >0 means pressed
*/
uint8_t read_button(uint8_t button);

#endif