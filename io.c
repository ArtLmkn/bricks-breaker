/*******************************************************************
  Program to save addresses of input and output devices 
  and work with them.

  io.c      - working with inputs and outputs

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "imports.h"



IO initIO() {
    IO io;

    // Create adresses
    io.base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    io.lcd = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    io.knob = (volatile uint32_t*)(io.base + SPILED_REG_KNOBS_8BIT_o);
    io.led = (volatile uint32_t*)(io.base + SPILED_REG_LED_LINE_o);
    io.rgb1 = (volatile uint32_t*)(io.base + SPILED_REG_LED_RGB1_o);
    io.rgb2 = (volatile uint32_t*)(io.base + SPILED_REG_LED_RGB2_o);

    io.button = false;
    io.value = ((*io.knob) & IO_VALUE) >> 8;
    parlcd_hx8357_init(io.lcd); // LCD initialisatoin

    return io;
}



bool buttonClicked(IO *io) {
    // Button was pressed
    if (((*io->knob) & IO_BUTTON) >> 25) io->button = true;

    // Button was released
    if (!(((*io->knob) & IO_BUTTON) >> 25) && io->button) {
        io->button = false;
        return true;
    }

    return false;
}



uint8_t buttonSpinned(IO *io) {
    uint8_t newValue = ((*io->knob) & IO_VALUE) >> 8; // Knob value after spinning

    if (io->value == 252 && newValue < 50) { // Moving across 0 to the right
        io->value = newValue;
        return IO_RIGHT;
    } else if (io->value == 0 && newValue > 200) { // Moving across 0 to the left
        io->value = newValue;
        return IO_LEFT;
    } else if (newValue >= io->value + 4) { // Moving normally to the right
        io->value = newValue;
        return IO_RIGHT; 
    } else if (newValue <= io->value - 4) { // Moving normally to the left
        io->value = newValue;
        return IO_LEFT;
    } 

    return 0; // Knob wasn't spinned
}



void setLED(IO *io, uint8_t value) {
    switch (value) {
        case 3:
            *io->led = IO_LIVES_3;
            break;
        case 2:
            *io->led = IO_LIVES_2;
            break;
        case 1:
            *io->led = IO_LIVES_1;
            break;
        default:
            *io->led = IO_LIVES_0;
    }

}



void blinkRGB(IO *io, int color) {
    for (int i = 0; i < 3; ++i) {   // Triple blinking
        *io->rgb1 = color;
        *io->rgb2 = color;
        usleep(BLINKTIME);
        *io->rgb1 = IO_RGB_OFF;
        *io->rgb2 = IO_RGB_OFF;
        usleep(BLINKTIME);
    }
}
