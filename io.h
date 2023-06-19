/*******************************************************************
  Program to save addresses of input and output devices 
  and work with them.

  io.h      - working with inputs and outputs

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef __IO_H__
#define __IO_H__

#include "imports.h"

/*
 * Input/Output manager structure.
 *
 * @attribute base   - main IO address (uint8_t)
 * @attribute lcd    - LCD address (uint8_t)
 * @attribute knob   - knobs address (uint32_t)
 * @attribute led    - led address (uint32_t)
 * @attribute rgb1   - 1st rgb led address (uint32_t)
 * @attribute rgb2   - 2nd rgb led address (uint32_t)
 * @attribute button - is knob button is pressed (bool)
 * @attribute value  - knob actual value (uint8_t)
 */
typedef struct {
    uint8_t *base;
    uint8_t *lcd;
    volatile uint32_t *knob;
    volatile uint32_t *led;
    volatile uint32_t *rgb1;
    volatile uint32_t *rgb2;
    bool button;
    uint8_t value;
} IO;


/*
 * Function to initialize input/output manager.
 *
 * @return - input/output manager (IO)
 */
IO initIO();

/*
 * Function to detect was knob button clicked.
 *
 * @param io    - associated input/output manager (IO*)
 * @return      - is knob button klicked (bool)
 */
bool buttonClicked(IO *io);

/*
 * Function to detect was knob spinned.
 *
 * @param io    - associated input/output manager (IO*)
 * @return      - is knob spinned (uint8_t)
 */
uint8_t buttonSpinned(IO *io);

/*
 * Function to set LED strip.
 *
 * @param io    - associated input/output manager (IO*)
 * @param value - value to set on LED strip (uint8_t) 
 */
void setLED(IO *io, uint8_t value);

/*
 * Function to blink RGB LEDs.
 *
 * @param io    - associated input/output manager (IO*)
 * @param color - color to blink (int) 
 */
void blinkRGB(IO *io, int color);

#endif // __IO_H__
