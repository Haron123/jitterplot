#ifndef DRV8825_H
#define DRV8825_H

#include "stdint.h"
#include "system_time.h"

#define FORWARD 0
#define BACKWARD 1

#define FULLSTEP_MSK 0b000
#define HALFSTEP_MSK 0b001
#define FOURTHSTEP_MSK 0b010
#define EIGTHSTEP_MSK 0b011
#define SIXTEENTHSTEP_MSK 0b100
#define THIRTYTWOSTEP_MSK 0b101

typedef struct Pin_Port_Pair
{
  volatile uint8_t* port;
  uint8_t pin;
} Pin_Port_Pair;

typedef struct DRV8825
{
  Pin_Port_Pair m0;
  Pin_Port_Pair m1;
  Pin_Port_Pair m2;
  Pin_Port_Pair sleep;
  Pin_Port_Pair step;
  Pin_Port_Pair dir;

  uint8_t microstep_mode;

} DRV8825;

DRV8825 drv_create(Pin_Port_Pair m0, Pin_Port_Pair m1, Pin_Port_Pair m2,
Pin_Port_Pair sleep, Pin_Port_Pair step, Pin_Port_Pair dir);

void drv_step(DRV8825* drv8825, uint16_t steps, uint8_t direction);

void drv_set_microstep(DRV8825* drv8825, uint8_t microstep_mask);

void drv_disable(DRV8825* drv8825);

void drv_enable(DRV8825* drv8825);

#endif