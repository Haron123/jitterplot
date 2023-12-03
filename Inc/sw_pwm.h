#ifndef SW_PWM_H
#define SW_PWM_H

#include <avr/interrupt.h>
#include "system_time.h"

// Due to each added Pin slowing down the system
// the maximum should be determined
#define SW_PWM_MAX_PINS 10

// The Time it waits before
// The Interrupt updates the Pwm Pins
// Lower numbers make the PWM more accurate butS
// slow down the overall system
// Time is given in Microseconds
#define SW_PWM_POLL_TIME 120

#define TIMER0_CLOCK 16000000

// Both Macros have to be updated at the same time
// one is used for the register value
// the other is used to make further calculations possible
#define TIMER0_PRESCALER_REGVAL TIMER0_PRESCALER_8
#define TIMER0_PRESCALER_NUMBER 8

#define TIMER0_SECOND (TIMER0_CLOCK / TIMER0_PRESCALER_NUMBER)
#define TIMER0_MILLISECOND (TIMER0_SECOND / 1000)
#define TIMER0_MICROSECOND (TIMER0_MILLISECOND / 1000)

// Mapping Prescaler to actual register values
// For the atmega328p TIMER0
#if(mcu == atmega328p)
#define TIMER0_PRESCALER_OFF 0b0000
#define TIMER0_PRESCALER_1 0b0001
#define TIMER0_PRESCALER_8 0b0010
#define TIMER0_PRESCALER_64 0b0011
#define TIMER0_PRESCALER_256 0b0100
#define TIMER0_PRESCALER_1024 0b0101
#endif

/*
pwm_period is the period of the pwm, determining the frequency
duty cycle is the period of the pwm_period where the pin should be high
last_update keeps track of the updates it got
*/
typedef struct PwmPin
{
    volatile uint8_t* port;
    uint8_t pin;

    tTime high_period;
    tTime pwm_period;
    tTime last_update;
} PwmPin;

/**
 * @brief sets the Timer and Interrupt used to control the Pwm Pins
*/
void sw_pwm_init(void);

/**
 * @brief Creates a PWM Pin, automatically calculates the pwm_period
 * and high_period with the given parameters
 * 
 * @param port the Port the pwm pin is on
 * @param pin the pin you wanna pulse
 * @param freq the frequency of the signal. Be aware of the 
 * upper frequency limit set in the macros
 * @param duty_cycle the percentage of the time, the Pin is High
 * can be 0-100 representing 0% to 100%. Be aware of the 
 * lower duty_cycle limit set in the macros
*/
PwmPin sw_pwm_create_pin(volatile uint8_t* port, uint8_t pin, uint32_t freq, uint8_t duty_cycle);

/**
 * @brief changes the frequency of a created pwm_pin, automatically
 * calculates the pwm_period
 * 
 * @param pwmpin the PwmPin you want to change the frequency of
 * @param new_freq the new frequency to set the pwmpin to
*/
void sw_pwm_change_freq(PwmPin* pwmpin, uint32_t new_freq);

/**
 * @brief changes the duty_cycle of a created pwm_pin, automatically
 * calculates the high_period
 * 
 * @param pwmpin the PwmPin you want to change the frequency of
 * @param new_duty_cycle the new duty_cycle to set the pwmpin to
*/
void sw_pwm_change_duty_cycle(PwmPin* pwmpin, uint8_t new_duty_cycle);

/**
 * @brief adds the specified pin to the Modules Array of pins,
 * that get iterated through, the more pins you add the more time
 * it needs to iterate, adding to the system latency.
 * Be aware of the maximum amount of allowed Pins.
 * 
 * @param pwmpin the PwmPin you wanna add to the Array
*/
void sw_pwm_add_pin(PwmPin* pwmpin);

/**
 * @brief updates all pwm pins state
*/
void sw_pwm_update_all();

#endif