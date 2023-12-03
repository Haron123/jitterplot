#include "buttons.h"

uint8_t read_button(uint8_t button)
{
  return (PIND & (1 << button));
}