#include "drv8825.h"

DRV8825 drv_create(Pin_Port_Pair m0, Pin_Port_Pair m1, Pin_Port_Pair m2,
Pin_Port_Pair sleep, Pin_Port_Pair step, Pin_Port_Pair dir)
{
  DRV8825 temp;

  temp.m0 = m0;
  temp.m1 = m1;
  temp.m2 = m2;
  temp.sleep = sleep;
  temp.step = step;
  temp.dir = dir;

  // Full step mode
  temp.microstep_mode = FULLSTEP_MSK;

  return temp;
}

void drv_step(DRV8825* drv8825, uint16_t steps, uint8_t direction)
{
  volatile uint8_t* step_port = drv8825->step.port;
  uint8_t step_pin = drv8825->step.pin;

  volatile uint8_t* dir_port = drv8825->dir.port;
  uint8_t dir_pin = drv8825->dir.pin;

  // Consider the microsteps, for the step
  uint16_t actual_steps = steps * (1 << drv8825->microstep_mode);

  // Setup the direction of the Driver
  if(direction == FORWARD)
  {
    *dir_port &= ~(1 << dir_pin);
  }
  else if(direction == BACKWARD)
  {
    *dir_port |= (1 << dir_pin);
  }
  
  // Repeat a step till we reach the desired steps
  for(uint16_t i = 0; i < steps; i++)
  {
    *step_port |= (1 << step_pin);
    delay_ms(1);
    *step_port &= ~(1 << step_pin);
    delay_ms(1);
  }
}

void drv_set_microstep(DRV8825* drv8825, uint8_t microstep_mask)
{
  // Binary and operation, ensures we dont break other code incase someone inserts a nonvalid mask
  drv8825->microstep_mode = microstep_mask & (0b111);

  *(drv8825->m0.port) &= ~(1 << drv8825->m0.pin);
  *(drv8825->m1.port) &= ~(1 << drv8825->m1.pin);
  *(drv8825->m2.port) &= ~(1 << drv8825->m2.pin);
  
  *(drv8825->m0.port) |= drv8825->microstep_mode & 1;
  *(drv8825->m1.port) |= drv8825->microstep_mode & 2;
  *(drv8825->m2.port) |= drv8825->microstep_mode & 4;
}

void drv_disable(DRV8825* drv8825)
{
  volatile uint8_t* sleep_port = drv8825->sleep.port;
  uint8_t sleep_pin = drv8825->sleep.pin;

  *sleep_port |= (1 << sleep_pin);
}

void drv_enable(DRV8825* drv8825)
{
  volatile uint8_t* sleep_port = drv8825->sleep.port;
  uint8_t sleep_pin = drv8825->sleep.pin;

  *sleep_port &= ~(1 << sleep_pin);
}