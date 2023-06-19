/*******************************************************************
  Program to create and update playing proccess 
  of Bricks Breaker game.

  level.h      - playing proccess controling

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "imports.h"

/*
 * Game object structure.
 *
 * @attribute x      - x coordinate (int16_t)
 * @attribute y      - y coordinate (int16_t)
 * @attribute w      - object width (uint16_t)
 * @attribute h      - object height (uint16_t)
 * @attribute health - object health (uint8_t)
 */
typedef struct {
    int16_t x;
    int16_t y;
    uint16_t w;
    uint16_t h;
    uint8_t health;
} GameObj;

/*
 * Game object structure.
 *
 * @attribute dx    - movement at x axis (int8_t)
 * @attribute dy    - movement at y axis (int8_t)
 */
typedef struct {
    int8_t dx;
    int8_t dy;
} Movement;

/*
 * Game manager structure.
 *
 * @attribute level         - current level number (uint8_t)
 * @attribute speed         - current level speed (uint8_t)
 * @attribute score         - current game score (uint32_t)
 * @attribute bricks        - array of bricks (GameObj*)
 * @attribute platform      - platform/player (GameObj)
 * @attribute ball          - ball (GameObj)
 * @attribute bricksCount   - current bricks at level (uint8_t)
 * @attribute paused        - is game proccess paused (bool)
 */
typedef struct {
    uint8_t level;
    uint8_t speed;
    uint32_t score;
    GameObj *bricks;
    GameObj platform;
    GameObj ball;
    uint8_t bricksCount;
    bool paused;
} Level;


/*
 * Function to initialize game manager.
 *
 * @return - game manager (Level)
 */
Level initLevel();

/*
 * Function to load level from binary file.
 *
 * @param state - current game state holder (uint8_t*)
 * @param level - current level element (Level*) 
 */
void loadLevel(uint8_t *state, Level *level);

/*
 * Function to update game proccess.
 *
 * @param io         - associated input/output manager (IO*)
 * @param level      - current level element (Level*) 
 * @param move       - ball move directions (Movement*)
 * @param bricksLeft - actual bricks at level (uint8_t*)
 */
void updateLevel(IO *io, Level *level, Movement *move, uint8_t *bricksLeft);

/*
 * Function to set level status to default (paused and platform centered)
 * and set player health.
 *
 * @param level     - current level element (Level*) 
 * @param health    - player health to set (uint8_t)
 * @param move      - ball move directions (Movement*)
 */
void setLevel(Level *level, uint8_t health, Movement *move);

#endif // __LEVEL_H__
