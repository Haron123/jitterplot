#include "jitterplot.h"

Jitter_Plot plot_create(Pin_Port_Pair m0, Pin_Port_Pair m1, Pin_Port_Pair m2,
Pin_Port_Pair sleep, Pin_Port_Pair x_step, Pin_Port_Pair x_dir, Pin_Port_Pair y_step, Pin_Port_Pair y_dir, Pin_Port_Pair pen_servo)
{
  Jitter_Plot temp;

  // Setup shared pins
  temp.x_stepper.m0 = m0;
  temp.x_stepper.m1 = m1;
  temp.x_stepper.m2 = m2;
  temp.x_stepper.sleep = sleep;

  temp.y_stepper.m0 = m0;
  temp.y_stepper.m1 = m1;
  temp.y_stepper.m2 = m2;
  temp.y_stepper.sleep = sleep;

  // Setup x-axis specific pins
  temp.x_stepper.step = x_step;
  temp.x_stepper.dir = x_dir;

  // Setup y-axis specific pins
  temp.y_stepper.step = y_step;
  temp.y_stepper.dir = y_dir;

  temp.current_x = 0;
  temp.current_y = 0;

  // Setup Servo for Pen
  temp.pen_servo = sw_pwm_create_pin(pen_servo.port, pen_servo.pin, 50, 0);

  return temp;
}

static int8_t check_coord(Jitter_Plot* plotter)
{
  if(plotter->current_x >= CANVAS_WIDTH || plotter->current_x < 0)
  {
    oled_write_str("out of bounds", sizeof("out of bounds"));
    return -1;
  }

  if(plotter->current_y >= CANVAS_HEIGHT || plotter->current_y < 0)
  {
    oled_write_str("out of bounds", sizeof("out of bounds"));
    return -1;
  }

  return 0;
}

void plotter_set_microstep(Jitter_Plot* plotter, uint8_t microstep_mask)
{
  drv_set_microstep(&(plotter->x_stepper), microstep_mask);
  drv_set_microstep(&(plotter->y_stepper), microstep_mask);
}

// Change the directions if u dont wanna change ur wiring :
void plotter_step_right(Jitter_Plot* plotter, uint16_t distance)
{
  if(plotter->current_x <= CANVAS_WIDTH)
  {
    drv_step(&(plotter->x_stepper), distance, BACKWARD);
    plotter->current_x += distance;
  }
}

void plotter_step_left(Jitter_Plot* plotter, uint16_t distance)
{
  if(plotter->current_x >= 0)
  {
    drv_step(&(plotter->x_stepper), distance, FORWARD);
    plotter->current_x -= distance;
  }
}

void plotter_step_up(Jitter_Plot* plotter, uint16_t distance)
{
  if(plotter->current_y > 0)
  {
    drv_step(&(plotter->y_stepper), distance, FORWARD);
    plotter->current_y -= distance;
  }
}

void plotter_step_down(Jitter_Plot* plotter, uint16_t distance)
{
  if(plotter->current_y < CANVAS_HEIGHT)
  {
    drv_step(&(plotter->y_stepper), distance, BACKWARD);
    plotter->current_y += distance;
  }
}

void plotter_pen_down(Jitter_Plot* plotter)
{
  #if 1
  sw_pwm_change_duty_cycle(&(plotter->pen_servo), 4);
  _delay_ms(250);
  #endif
}

void plotter_pen_up(Jitter_Plot* plotter)
{
  #if 1
  sw_pwm_change_duty_cycle(&(plotter->pen_servo), 7);
  _delay_ms(250);
  sw_pwm_change_duty_cycle(&(plotter->pen_servo), 0);
  _delay_ms(250);
  #endif 
}

void plotter_off(Jitter_Plot* plotter)
{
  drv_disable(&(plotter->x_stepper));
}

void plotter_on(Jitter_Plot* plotter)
{
  drv_enable(&(plotter->x_stepper));
}
