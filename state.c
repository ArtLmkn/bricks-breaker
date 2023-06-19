/*******************************************************************
  Program holding different game states.

  state.c      - game states logic

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "imports.h"



void menu(GUI *gui, IO *io, uint8_t *state) {
    // Create buttons
    uint8_t active = GUI_BUTTON_PLAY;
    bool buttons[2] = {true, false};
    
    draw(gui, gui->backgrounds[GUI_BACKGROUND_MAIN], 0, 0, GUI_BACKGROUND_W, GUI_BACKGROUND_H); // Drawing background

    while (true) {
        draw(gui, gui->buttons[GUI_BUTTON_PLAY][buttons[0]], GUI_BUTTON_X, GUI_BUTTON_Y3, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing 1st button
        draw(gui, gui->buttons[GUI_BUTTON_QUIT][buttons[1]], GUI_BUTTON_X, GUI_BUTTON_Y4, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing 2nd button
        render(gui, io); // Render screen

        // Knob rotation listener
        uint8_t rotation = buttonSpinned(io);
        if (rotation) {
            active = (active + 5) % 10;
            for (uint8_t i = 0; i < sizeof(buttons); ++i) buttons[i] = !buttons[i] ? true : false;
        }
    
        // Knob pressing listener
        if (buttonClicked(io)){
            if (active == GUI_BUTTON_PLAY) *state = STATE_PLAY;
            else if (active == GUI_BUTTON_QUIT) *state = STATE_EXIT;
            break;
        }
    }
}



void play(GUI *gui, IO *io, uint8_t *state, Level *level) {
    // Create buttons
    uint8_t active = GUI_BUTTON_START - 1;
    bool buttons[4] = {true, false, false, false};
    
    draw(gui, gui->backgrounds[GUI_BACKGROUND_BLANK], 0, 0, GUI_BACKGROUND_W, GUI_BACKGROUND_H); // Drawing background

    while (true) { 
        draw(gui, gui->buttons[GUI_BUTTON_START][buttons[0]], GUI_BUTTON_X, GUI_BUTTON_Y1, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing 1st button
        draw(gui, gui->buttons[GUI_BUTTON_LEVEL][buttons[1]], GUI_BUTTON_X, GUI_BUTTON_Y2, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing 2nd button
        draw(gui, gui->buttons[GUI_BUTTON_SPEED][buttons[2]], GUI_BUTTON_X, GUI_BUTTON_Y3, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing 3rd button
        draw(gui, gui->buttons[GUI_BUTTON_BACK][buttons[3]], GUI_BUTTON_X, GUI_BUTTON_Y4, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing 4th button
        draw(gui, gui->digits[level->level], GUI_DIGIT_X1, GUI_DIGIT_Y1, GUI_DIGIT_W, GUI_DIGIT_H); // Drawing 1st digit
        draw(gui, gui->digits[level->speed], GUI_DIGIT_X1, GUI_DIGIT_Y1 + 64, GUI_DIGIT_W, GUI_DIGIT_H); // Drawing 2nd digit
        render(gui, io); // Render screen

        // Knob rotation listener
        uint8_t rotation = buttonSpinned(io);
        if (rotation == IO_RIGHT) active = (active + 1) % sizeof(buttons);
        else if (rotation == IO_LEFT) active = (active - 1) % sizeof(buttons);
        for (uint8_t i = 0; i < sizeof(buttons); ++i) buttons[i] = i == active ? true : false;
    
        // Knob pressing listener
        if (buttonClicked(io)){
            if (active == GUI_BUTTON_LEVEL - 1) {   // Increase level number
                level->level = level->level % 5 + 1;
                continue;
            }
            else if (active == GUI_BUTTON_SPEED - 1) {  // Increase level speed
                level->speed = level->speed % 5 + 1;
                continue;
            }
            else if (active == GUI_BUTTON_START - 1) *state = STATE_GAME;
            else if (active == GUI_BUTTON_BACK - 1) *state = STATE_MENU;
            break;
        }
    }
}



void game(GUI *gui, IO *io, uint8_t *state, Level *level) {
    // Preparations before playing
    loadLevel(state, level);
    Movement move = {-1, -1};
    setLevel(level, 3, &move);
    uint8_t bricksLeft = level->bricksCount;

    // Playing loop
    while (true) {
        draw(gui, gui->backgrounds[GUI_BACKGROUND_BLANK], 0, 0, GUI_BACKGROUND_W, GUI_BACKGROUND_H); // Drawing background

        for (int i = 0; i < level->bricksCount; ++i) {  // Drawing bricks
            GameObj brick = level->bricks[i];
            draw(gui, gui->bricks[brick.health], brick.x, brick.y, brick.w, brick.h);
        }

        draw(gui, gui->platform, level->platform.x, level->platform.y, level->platform.w, level->platform.h); // Drawing platform
        draw(gui, gui->ball, level->ball.x, level->ball.y, level->ball.w, level->ball.h); // Drawing ball
        render(gui, io); // Render screen

        setLED(io, level->platform.health); // Show player lives

        if (!level->paused) updateLevel(io, level, &move, &bricksLeft);

        if (!bricksLeft || !level->platform.health) {   // Game finished
            level->paused = false;
            *state = STATE_SCORE;
            break;
        }

        // Knob rotation listener
        uint8_t rotation = buttonSpinned(io);
        if (rotation == IO_RIGHT && level->platform.x <= LEVEL_PLAYER_LIMIT_R) {
            level->platform.x += LEVEL_PLAYER_STEP;
            level->ball.x = level->paused ? level->ball.x + LEVEL_PLAYER_STEP : level->ball.x;
        } else if (rotation == IO_LEFT && level->platform.x >= LEVEL_PLAYER_LIMIT_L) {
            level->platform.x -= LEVEL_PLAYER_STEP;
            level->ball.x = level->paused ? level->ball.x - LEVEL_PLAYER_STEP : level->ball.x;
        }

        // Knob pressing listener
        if (buttonClicked(io)){
            if (level->paused) {
                level->paused = false;
            } else {
                blinkRGB(io, IO_RGB_RED);
                setLevel(level, level->platform.health - 1, &move);
            }
        }
    }
}



void score(GUI *gui, IO *io, uint8_t *state, Level *level) {
    if (!level->platform.health) { // Drawing lose background
        printf(LOG_LOSE, level->score);
        draw(gui, gui->backgrounds[GUI_BACKGROUND_LOSE], 0, 0, GUI_BACKGROUND_W, GUI_BACKGROUND_H);
    } else { // Drawing win background
        printf(LOG_WIN, level->score);
        blinkRGB(io, IO_RGB_GREEN);
        draw(gui, gui->backgrounds[GUI_BACKGROUND_WIN], 0, 0, GUI_BACKGROUND_W, GUI_BACKGROUND_H);
    }

    level->score += (10000 * level->platform.health * level->speed); // Convert lives to score

    // Resets after playing
    setLED(io, IO_LIVES_0); // Reset player lives
    if (level->bricks) free(level->bricks); // Clearing bricks for level
    level->bricksCount = 0;
    level->paused = true;
    
    for (int i = 0; i < 6; ++i) { // Draw score
        uint8_t digit = (uint8_t)(level->score / 100000);
        level->score %= 100000;
        level->score *= 10;
        draw(gui, gui->digits[digit], GUI_DIGIT_X2 + 2 * i * GUI_DIGIT_W, GUI_DIGIT_Y2, GUI_DIGIT_W, GUI_DIGIT_H);
    }

    draw(gui, gui->buttons[GUI_BUTTON_BACK][1], GUI_BUTTON_X, GUI_BUTTON_Y4, GUI_BUTTON_W, GUI_BUTTON_H); // Drawing button
    
    render(gui, io); // Render screen

    while (true) { 
        // Knob pressing listener
        if (buttonClicked(io)){
            *state = STATE_MENU;
            break;
        }
    }
}
