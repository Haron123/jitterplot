#include "static_letter_function.h"

void draw(Jitter_Plot* plotter, uint16_t font_size, const char* letter_array)
{
  int16_t letter_x = 0;
  int16_t letter_y = 0;
  uint16_t i = 0;
  plotter_on(plotter);
  while(letter_array[i] != 0)
  {
    /* Repeat for each letter in the command */
    if(letter_array[i] == 'G')
    {
      /* G(oto) Command is received and executed*/
      plotter_step_right(plotter, (letter_array[i+1] - '0') * font_size);
      letter_x += (letter_array[i+1] - '0') * font_size;
      plotter_step_down(plotter, (letter_array[i+2] - '0') * font_size);
      letter_y += (letter_array[i+2] - '0') * font_size;
      i+= 2;
      plotter_pen_down(plotter);
    }
    else
    {
      /* If a Direction command is received follow it*/
      for(uint16_t j = 0; j < font_size; j++)
      {
        switch(letter_array[i])
        {      
            case TOP :  plotter_step_up(plotter, 1); letter_y--; break;
            case RIGHT :  plotter_step_right(plotter, 1); letter_x++; break;
            case BOTTOM :  plotter_step_down(plotter, 1); letter_y++; break;
            case LEFT :  plotter_step_left(plotter, 1); letter_x--; break;
            case TOP_RIGHT :  plotter_step_up(plotter, 1); plotter_step_right(plotter, 1);  letter_y--; letter_x++; break;
            case BOTTOM_RIGHT :  plotter_step_down(plotter, 1); plotter_step_right(plotter, 1); letter_y++; letter_x++; break;
            case BOTTOM_LEFT :  plotter_step_down(plotter, 1); plotter_step_left(plotter, 1); letter_y++; letter_x--; break;
            case TOP_LEFT :  plotter_step_up(plotter, 1); plotter_step_left(plotter, 1);  letter_y--;letter_x--;  break;
        }
      }
    }
    /* dududu */
    ++i;
  }
  /* Get Plotter ready incase there is another Letter incoming*/
  plotter_pen_up(plotter);
  if(letter_y >= 0)
  {
    plotter_step_up(plotter, letter_y);
  }
  else
  {
    plotter_step_down(plotter, -letter_y);
  }
  
  plotter_step_right(plotter, (5*font_size) - letter_x);
  plotter_off(plotter);
}