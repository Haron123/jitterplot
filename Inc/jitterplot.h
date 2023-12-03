#ifndef JITTER_PLOT_H
#define JITTER_PLOT_H

#include "drv8825.h"
#include "sw_pwm.h"
#include "avr/io.h"
#include "ssd1306.h"
#include "util/delay.h"

#define CANVAS_WIDTH 3000
#define CANVAS_HEIGHT 2000

#define MARGIN_SIDES 3
#define MARGIN_UPDOWN 3

typedef struct Jitter_Plot 
{
  DRV8825 x_stepper;
  DRV8825 y_stepper;
  PwmPin pen_servo;

  int16_t current_x;
  int16_t current_y;
} Jitter_Plot;

/**
 * @brief creates and sets up a jitter_plot struct and returns it with the given parameters
 * @param m0 m0 pin for both DRV8825
 * @param m1 m1 pin for both DRV8825
 * @param m2 m2 pin for both DRV8825
 * @param sleep sleep pin for both DRV8825
 * 
 * X-AXIS :
 * @param x_step pin for the step pin of the DRV8825 responsible for the x-axis
 * @param x_dir pin for the dir pin of the DRV8825 responsible for the x-axis
 * 
 * Y-AXIS :
 * @param y_step pin for the step pin of the DRV8825 responsible for the y-axis
 * @param y_dir pin for the dir pin of the DRV8825 responsible for the y-axis
 * 
 * PEN-HOLDER :
 * @param pen_servo pin connected to the pwm input of the servo of the penholder
 * 
 * @retval Created and Initialized Jitter_Plot struct with the given parameters
*/
Jitter_Plot plot_create(Pin_Port_Pair m0, Pin_Port_Pair m1, Pin_Port_Pair m2,
Pin_Port_Pair sleep, Pin_Port_Pair x_step, Pin_Port_Pair x_dir, Pin_Port_Pair y_step, Pin_Port_Pair y_dir, Pin_Port_Pair pen_servo);

/* TODO: Documentation*/

void plotter_set_microstep(Jitter_Plot* plotter, uint8_t microstep_mask);

void plotter_step_right(Jitter_Plot* plotter, uint16_t distance);

void plotter_step_left(Jitter_Plot* plotter, uint16_t distance);

void plotter_step_up(Jitter_Plot* plotter, uint16_t distance);

void plotter_step_down(Jitter_Plot* plotter, uint16_t distance);

void plotter_pen_down(Jitter_Plot* plotter);

void plotter_pen_up(Jitter_Plot* plotter);

void plotter_off(Jitter_Plot* plotter);

void plotter_on(Jitter_Plot* plotter);

#endif