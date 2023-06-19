/*******************************************************************
  Program to load and use graphical user interface
  in Bricks Bracker game on MZAPO device.

  gui.c      - connection gui to device

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "imports.h"



GUI initGUI(uint8_t *state) {
    GUI gui;

    loadBackgrounds(state, gui.backgrounds);
    loadButtons(state, gui.buttons);
    loadDigits(state, gui.digits);
    loadBricks(state, gui.bricks);
    loadPlatform(state, gui.platform);
    loadBall(state, gui.ball);

    gui.frameBuffer = (uint16_t *)malloc(GUI_W * GUI_H * 2);
    if (!gui.frameBuffer) {     // Memory allocation control
        printf(LOG_ERROR_MALLOC);
        *state = STATE_EXIT;
    }

    return gui;
}



void loadBackgrounds(uint8_t *state, uint16_t (*backgrounds)[GUI_BACKGROUND_W * GUI_BACKGROUND_H]) {
    FILE *file = fopen(GUI_BACKGROUND, "rb");
    if (!file) {    // File open control
        printf(LOG_ERROR_BACKGROUND);
        *state = STATE_EXIT;
        return;
    }
    
    for (int i = 0; i < 4; ++i) while (fgetc(file) != NL) continue; // Skip file header
    for (int i = 0; i < GUI_BACKGROUND_COUNT; ++i) { // Load images from file
        for (int j = 0; j < GUI_BACKGROUND_H * GUI_BACKGROUND_W; ++j) {
            uint8_t r = fgetc(file);
            uint8_t g = fgetc(file);
            uint8_t b = fgetc(file);
            backgrounds[i][j] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); // RGB888->RGB565
        }
    }

    fclose(file); 
    printf(LOG_BACKGROUND);
}



void loadButtons(uint8_t *state, uint16_t (*buttons)[2][GUI_BUTTON_W * GUI_BUTTON_H]) {
    FILE *file = fopen(GUI_BUTTON, "rb");
    if (!file) {    // File open control
        printf(LOG_ERROR_BUTTON);
        *state = STATE_EXIT;
        return;
    }
    
    for (int i = 0; i < 4; ++i) while (fgetc(file) != NL) continue; // Skip file header
    for (int i = 0; i < GUI_BUTTON_COUNT * 2; ++i) { // Load images from file
        for (int j = 0; j < GUI_BUTTON_H * GUI_BUTTON_W; ++j) {
            uint8_t r = fgetc(file);
            uint8_t g = fgetc(file);
            uint8_t b = fgetc(file);
            buttons[i%GUI_BUTTON_COUNT][i/GUI_BUTTON_COUNT][j] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); // RGB888->RGB565
        }
    }

    fclose(file); 
    printf(LOG_BUTTON);
}



void loadDigits(uint8_t *state, uint16_t (*digits)[GUI_DIGIT_W * GUI_DIGIT_H]) {
    FILE *file = fopen(GUI_DIGIT, "rb");
    if (!file) {    // File open control
        printf(LOG_ERROR_DIGIT);
        *state = STATE_EXIT;
        return;
    }
    
    for (int i = 0; i < 4; ++i) while (fgetc(file) != NL) continue; // Skip file header
    for (int i = 0; i < GUI_DIGIT_COUNT; ++i) { // Load images from file
        for (int j = 0; j < GUI_DIGIT_H * GUI_DIGIT_W; ++j) {
            uint8_t r = fgetc(file);
            uint8_t g = fgetc(file);
            uint8_t b = fgetc(file);
            digits[i][j] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); // RGB888->RGB565
        }
    }

    fclose(file); 
    printf(LOG_DIGIT);
}



void loadBricks(uint8_t *state, uint16_t (*bricks)[GUI_BRICK_W * GUI_BRICK_H]) {
    FILE *file = fopen(GUI_BRICK, "rb");
    if (!file) {    // File open control
        printf(LOG_ERROR_BRICK);
        *state = STATE_EXIT;
        return;
    }
    
    for (int i = 0; i < 4; ++i) while (fgetc(file) != NL) continue; // Skip file header
    for (int i = 0; i < GUI_BRICK_COUNT; ++i) { // Load images from file
        for (int j = 0; j < GUI_BRICK_H * GUI_BRICK_W; ++j) {
            uint8_t r = fgetc(file);
            uint8_t g = fgetc(file);
            uint8_t b = fgetc(file);
            bricks[i][j] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); // RGB888->RGB565
        }
    }

    fclose(file);
    printf(LOG_BRICK);
}



void loadPlatform(uint8_t *state, uint16_t *platform) {
    FILE *file = fopen(GUI_PLATFORM, "rb");
    if (!file) {    // File open control
        printf(LOG_ERROR_PLATFORM);
        *state = STATE_EXIT;
        return;
    }
    
    for (int i = 0; i < 4; ++i) while (fgetc(file) != NL) continue; // Skip file header
    for (int i = 0; i < GUI_PLATFORM_H * GUI_PLATFORM_W; ++i) { // Load images from file
        uint8_t r = fgetc(file);
        uint8_t g = fgetc(file);
        uint8_t b = fgetc(file);
        platform[i] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); // RGB888->RGB565
    }

    fclose(file); 
    printf(LOG_PLATFORM);
}



void loadBall(uint8_t *state, uint16_t *ball) {
    FILE *file = fopen(GUI_BALL, "rb");
    if (!file) {    // File open control
        printf(LOG_ERROR_BALL);
        *state = STATE_EXIT;
        return;
    }
    
    for (int i = 0; i < 4; ++i) while (fgetc(file) != NL) continue; // Skip file header
    for (int i = 0; i < GUI_BALL_H * GUI_BALL_W; ++i) { // Load images from file
        uint8_t r = fgetc(file);
        uint8_t g = fgetc(file);
        uint8_t b = fgetc(file);
        ball[i] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); // RGB888->RGB565
    }

    fclose(file); 
    printf(LOG_BALL);
}



void draw(GUI *gui, uint16_t *object, int x, int y, int w, int h) {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            (gui->frameBuffer)[(i + y) * GUI_W + (j + x)] = object[i * w + j];
        }
    }
}



void render(GUI *gui, IO *io) {
    parlcd_write_cmd(io->lcd, 0x2c);
    for (int i = 0; i < GUI_W * GUI_H; ++i) {
        parlcd_write_data(io->lcd, gui->frameBuffer[i]);
    }
}
