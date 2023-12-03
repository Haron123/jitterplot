#ifndef STATIC_LETTER_FUNC_H
#define STATIC_LETTER_FUNC_H

#include "jitterplot.h"
#include "ssd1306.h"

#define TOP '0'
#define RIGHT '1'
#define BOTTOM '2'
#define LEFT '3'
#define TOP_RIGHT '4'
#define BOTTOM_RIGHT '5'
#define BOTTOM_LEFT '6'
#define TOP_LEFT '7' 

/**
 * @brief draws the given letter_array containing commands with the jitterplot
 * @param font_size the size of the font
 * @param letter_array one of the defined arrays in this module (see above)
 * @retval none
*/
void draw(Jitter_Plot* plotter, uint16_t font_size, const char* letter_array);

#endif