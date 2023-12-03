#include "sw_pwm.h"

// Array to keep track of the Pins and add a
// Limit to it, knowing the hardware.
static PwmPin* sw_pwm_module_array[SW_PWM_MAX_PINS];
static uint32_t sw_pwm_array_index;

static inline void sw_pwm_update_pin(PwmPin* pwmpin);

ISR(TIMER0_COMPA_vect)
{
    sw_pwm_update_all();
    //PORTB ^= (1 << PB0);
}

/**
 * @brief Updates a specific pwm_pin, only should be
 * used by sw_pwm_update_all()
 * @param pwmpin, the pwmpin thats to update
*/
static inline void sw_pwm_update_pin(PwmPin* pwmpin)
{
    // Since this function only gets called by
    // sw_pwm_update_all(), which doesnt accept extra parameters
    // and sw_pwm_add_pin() ensures the pwmpins in the list
    // arent NULL, we can save the error_handling here
    // Since this needs to be super fast

    tTime passed_time = time_passed(pwmpin->last_update);
    volatile uint8_t* port = pwmpin->port;

    // Set the pin low if the duty cycle is 0
    if(pwmpin->high_period == 0)
    {
        *port &= ~(1 << pwmpin->pin);
        pwmpin->last_update = timer1_get_time();
    }
    // If already past the period time set the pin high
    else if(passed_time >= pwmpin->pwm_period)
    {
        *port |= (1 << pwmpin->pin);
        pwmpin->last_update = timer1_get_time();
    }
    // If not past the period time but past the high period
    // set the pin low
    else if(passed_time >= pwmpin->high_period)
    {
        *port &= ~(1 << pwmpin->pin);
    }
}

void sw_pwm_init()
{
    //cli();
    // Setup interrupt for timer0
    TCCR0A |= (1 << WGM01);
    TCCR0B = TIMER0_PRESCALER_REGVAL;

    OCR0A = 200;
    TIMSK0 = (1 << OCIE0A);
    
    sei();
}

/**
 * @brief iterates through all added Pwm Pins and
 * updates their status
*/
void sw_pwm_update_all()
{
    for(uint8_t i = 0; i < sw_pwm_array_index; i++)
    {
        PwmPin* current_pin = sw_pwm_module_array[i];
        
        sw_pwm_update_pin(current_pin);
    }
}

PwmPin sw_pwm_create_pin(volatile uint8_t* port, uint8_t pin, uint32_t freq, uint8_t duty_cycle)
{
    // due to calculating with ticks we convert it first
    uint32_t pwm_period = (TIMER1_SECOND / freq);

    // duty_cycle parameter is already received 100 times larger
    // than the percentage, so we just calculate with that and
    // divide at the end
    uint32_t high_period = (pwm_period * duty_cycle) / 100;

    PwmPin temp;
    temp.port = port;
    temp.pin = pin;
    temp.pwm_period = pwm_period;
    temp.high_period = high_period;
    temp.last_update = 0;

    return temp;
}

void sw_pwm_change_freq(PwmPin* pwmpin, uint32_t new_freq)
{
    // due to calculating with ticks we convert it first
    uint32_t pwm_period = (TIMER1_SECOND / new_freq);

    pwmpin->pwm_period = pwm_period;
}

void sw_pwm_change_duty_cycle(PwmPin* pwmpin, uint8_t new_duty_cycle)
{   
    // duty_cycle parameter is already received 100 times larger
    // than the percentage, so we just calculate with that and
    // divide at the end
    uint32_t high_period = (pwmpin->pwm_period * (uint32_t)new_duty_cycle) / (uint32_t)100;

    pwmpin->high_period = high_period;
}

void sw_pwm_add_pin(PwmPin* pwmpin)
{

  for(uint8_t i = 0; i < sw_pwm_array_index; i++)
  {
      if(sw_pwm_module_array[i] == pwmpin)
      {
          // Trying to add pwmpin that already exists
          return;
      }
  }
  sw_pwm_module_array[sw_pwm_array_index] = pwmpin;
  sw_pwm_array_index++;
}