/*******************************************************************
  Program to load and use graphical user interface
  in Bricks Bracker game on MZAPO device.

  gui.h      - connection gui to device

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef __GUI_H__
#define __GUI_H__

#include "imports.h"

/*
 * Graphical User Interface manager structure.
 *
 * @attribute backgrounds   - background images (uint16_t[][])
 * @attribute buttons       - button images (uint16_t[][][])
 * @attribute digits        - ditig images (uint16_t[][])
 * @attribute bricks        - brick images (uint16_t[][])
 * @attribute platform      - platform image (uint16_t[])
 * @attribute ball          - ball image (uint16_t[])
 * @attribute frameBuffer   - buffer to render at screen (uint16_t*)
 */
typedef struct {
    uint16_t backgrounds[GUI_BACKGROUND_COUNT][GUI_BACKGROUND_W * GUI_BACKGROUND_H];
    uint16_t buttons[GUI_BUTTON_COUNT][2][GUI_BUTTON_W * GUI_BUTTON_H];
    uint16_t digits[GUI_DIGIT_COUNT][GUI_DIGIT_W * GUI_DIGIT_H];
    uint16_t bricks[GUI_BRICK_COUNT][GUI_BRICK_W * GUI_BRICK_H];
    uint16_t platform[GUI_PLATFORM_W * GUI_PLATFORM_H];
    uint16_t ball[GUI_BALL_W * GUI_BALL_H];
    uint16_t *frameBuffer;
} GUI;

/*
 * Function to initialize GUI manager.
 *
 * @param state - current game state holder (uint8_t*)
 * @return - GUI manager (GUI)
 */
GUI initGUI(uint8_t *state);

/*
 * Function to load background images.
 *
 * @param state       - current game state (uint8_t*)
 * @param backgrounds - array of image buffers (uint16_t*[]) 
 */
void loadBackgrounds(uint8_t *state, uint16_t (*backgrounds)[GUI_BACKGROUND_W * GUI_BACKGROUND_H]);

/*
 * Function to load button images.
 *
 * @param state       - current game state (uint8_t*)
 * @param buttons     - array of image buffers (uint16_t*[][]) 
 */
void loadButtons(uint8_t *state, uint16_t (*buttons)[2][GUI_BUTTON_W * GUI_BUTTON_H]);

/*
 * Function to load digit images.
 *
 * @param state       - current game state (uint8_t*)
 * @param digits      - array of image buffers (uint16_t*[]) 
 */
void loadDigits(uint8_t *state, uint16_t (*digits)[GUI_DIGIT_W * GUI_DIGIT_H]);

/*
 * Function to load brick images.
 *
 * @param state       - current game state (uint8_t*)
 * @param bricks      - array of image buffers (uint16_t*[]) 
 */
void loadBricks(uint8_t *state, uint16_t (*bricks)[GUI_BRICK_W * GUI_BRICK_H]);

/*
 * Function to load platform image.
 *
 * @param state       - current game state (uint8_t*)
 * @param platform    - image buffer (uint16_t*) 
 */
void loadPlatform(uint8_t *state, uint16_t *platform);

/*
 * Function to load ball image.
 *
 * @param state       - current game state (uint8_t*)
 * @param ball        - image buffer (uint16_t*) 
 */
void loadBall(uint8_t *state, uint16_t *ball);

/*
 * Function to add image into frame buffer.
 *
 * @param gui       - associated GUI manager (GUI*)
 * @param object    - object to draw (uint16_t*) 
 * @param x         - x coordinate (int)
 * @param y         - y coordinate (int) 
 * @param w         - image width (int) 
 * @param h         - image height (int) 
 */
void draw(GUI *gui, uint16_t *object, int x, int y, int w, int h);

/*
 * Function to render frame buffer.
 *
 * @param gui       - associated GUI manager (GUI*)
 * @param io    - associated input/output manager (IO*)
 */
void render(GUI *gui, IO *io);

#endif // __GUI_H__
