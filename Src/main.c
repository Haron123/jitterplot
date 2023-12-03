#include <avr/io.h>

#include <stdlib.h>

#include "system_time.h"
#include "sw_pwm.h"
#include "ssd1306.h"
#include "drv8825.h"
#include "jitterplot.h"

#include "static_letter_function.h"

const char A[] = "G2066222200011112220000077";
const char B[] = "G0011152652633310001133000";
const char C[] = "G101115733622225114";
const char D[] = "G001115222263331000000";
const char E[] = "G4033332221113332221111";
const char F[] = "G403333222111333222";
const char G[] = "G417336222251110003";
const char H[] = "G0022222220001111000222222";
const char I[] = "G00113222222133";
const char J[] = "G3011322222637";
const char K[] = "G002222220001444666555";
const char L[] = "G00222221111";
const char M[] = "G00222222000000552044222222";
const char N[] = "G00222222000005554000222222";
const char O[] = "G012222511400007336";
const char P[] = "G00222222000111407333";
const char Q[] = "G101152226577563700004";
const char R[] = "G00111526325577033222000000";
const char S[] = "G4173362511526337";
const char T[] = "G00111133222222";
const char U[] = "G0022222511400000";
const char V[] = "G00222255440000";
const char W[] = "G00222225400225400000";
const char X[] = "G00255440266662044550";
const char Y[] = "G00225522004400";
const char Z[] = "G0011112666621111";

int main()
{ 
  init_system_tick();
  sw_pwm_init();
  oled_init();

  oled_set_cursor(0,0);
  oled_write_str("Initialized Periphs...", sizeof("Initialized Periphs..."));

  /* Setup the Pins */
  DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2);

  DDRC = (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
  DDRD = (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);

  PORTB &= ~(1 << PB0);

  oled_set_cursor(0,2);
  oled_write_str("Setup Pins...", sizeof("Setup Pins..."));

  /* Setup the Plotter*/
  Jitter_Plot plotter = plot_create((Pin_Port_Pair){&PORTC, 0}, (Pin_Port_Pair){&PORTC, 1}, (Pin_Port_Pair){&PORTC, 2}, 
  (Pin_Port_Pair){&PORTC, 3}, (Pin_Port_Pair){&PORTD, 2}, (Pin_Port_Pair){&PORTD, 3}, (Pin_Port_Pair){&PORTD, 0}, (Pin_Port_Pair){&PORTD, 1},
  (Pin_Port_Pair){&PORTB, 2});

  sw_pwm_add_pin(&(plotter.pen_servo));

  /* Get ready to start */
  plotter_off(&plotter);
  plotter_set_microstep(&plotter, THIRTYTWOSTEP_MSK);
  plotter_pen_up(&plotter);

  /* Draw Jitterplot*/
  draw(&plotter, 60, J);
  draw(&plotter, 60, I);
  draw(&plotter, 60, T);
  draw(&plotter, 60, T);
  draw(&plotter, 60, E);
  draw(&plotter, 60, R);
  draw(&plotter, 60, P);
  draw(&plotter, 60, L);
  draw(&plotter, 60, O);
  draw(&plotter, 60, T);
  // TODO: String support

  while(1)
  {
    
  }

  return 0;
}

