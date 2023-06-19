/*******************************************************************
  Program to create and update playing proccess 
  of Bricks Breaker game.

  level.c      - playing proccess controling

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "imports.h"



Level initLevel() {
    Level level;
    level.level = 1;
    level.speed = 1;
    level.score = 0;
    level.bricksCount = 0;
    level.paused = true;
    return level;
}



void loadLevel(uint8_t *state, Level *level) {
    // Available levels
    char *levels[5] = {LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5};
    uint8_t bricksCount[5] = {LEVEL_1_BRICKS, LEVEL_2_BRICKS, LEVEL_3_BRICKS, LEVEL_4_BRICKS, LEVEL_5_BRICKS};

    // Choose level
    FILE *file = fopen(levels[level->level - 1], "rb");
    level->bricksCount = bricksCount[level->level - 1];

    if (!file) { // File open control
        printf(LOG_ERROR_LEVEL);
        *state = STATE_EXIT;
        return;
    }

    level->bricks = malloc(level->bricksCount * sizeof(GameObj));
    if (!level->bricks) {   // Memory allocation control
        printf(LOG_ERROR_MALLOC);
        *state = STATE_EXIT;
        return;
    }

    // Load bricks
    uint16_t pos = 0;
    uint8_t health;
    for (int i = 0; i < GUI_GAMEPIX_COUNT; ++i) {
        for (int j = 0; j < GUI_GAMEPIX_COUNT; ++j) {
            health = fgetc(file);
            if (health) {
                GameObj brick = {j * GUI_GAMEPIX_W, i * GUI_GAMEPIX_H, GUI_BRICK_W, GUI_BRICK_H, health};
                level->bricks[pos++] = brick;
            }
        }
    }

    printf(LOG_LEVEL, level->level, level->speed);
}



void updateLevel(IO *io, Level *level, Movement *move, uint8_t *bricksLeft) {
    int16_t newX = level->ball.x + level->speed * move->dx; // x coordinate after move
    int16_t newY = level->ball.y + level->speed * move->dy; // y coordinate after move

    // Falling down
    if (newY + level->ball.h >= GUI_H) { 
        blinkRGB(io, IO_RGB_RED);
        setLevel(level, level->platform.health - 1, move);
        return;
    }
    
    // Bounces from edges
    if (newY <= 0) move->dy *= -1;
    if (newX <= 0 || newX + level->ball.w >= GUI_W) move->dx *= -1;

    // Bounces from platform
    if (newX + level->ball.w >= level->platform.x && newX <= level->platform.x + level->platform.w && newY + level->ball.h >= level->platform.y) move->dy *= -1;

    // Bounces from bricks
    for (int i = 0; i < level->bricksCount; ++i) {
        GameObj brick = level->bricks[i];
        if (brick.health && newX + level->ball.w / 2 >= brick.x && newX + level->ball.w / 2 <= brick.x + brick.w && newY + level->ball.h / 2 >= brick.y && newY + level->ball.h / 2 <= brick.y + brick.h) {
            if (newY + level->ball.h / 2 <= brick.y || newY + level->ball.h / 2 >= brick.y + brick.h) { // Colision from sides
                move->dx *= -1;
            } else { // Colision from top or bottom
                move->dy *= -1;
            }

            level->bricks[i].health--;
            level->score += (100 * level->speed);
            if (level->bricks[i].health == 0) (*bricksLeft)--;
            break;
        }
    }

    // Change ball coordinates
    level->ball.x += (level->speed * move->dx);
    level->ball.y += (level->speed * move->dy);
}



void setLevel(Level *level, uint8_t health, Movement *move) {
    level->paused = true;   // Pause game

    // Set platform to default position with given lives
    GameObj platform = {GUI_PLATFORM_X, GUI_PLATFORM_Y, GUI_PLATFORM_W, GUI_PLATFORM_H, health};
    level->platform = platform;

    // Set ball to default position
    GameObj ball = {level->platform.x + (level->platform.w - GUI_BALL_W) / 2, level->platform.y - GUI_BALL_H, GUI_BALL_W, GUI_BALL_H};
    level->ball = ball;

    // Set movement to default
    move->dx = -1;
    move->dy = -1;
}
