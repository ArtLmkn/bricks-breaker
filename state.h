/*******************************************************************
  Program holding different game states.

  state.h      - game states logic

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef __STATES_H__
#define __STATES_H__

#include "imports.h"

/*
 * Function holding main menu game state.
 *
 * @param gui   - associated graphical user interface (GUI*)
 * @param io    - associated input/output manager (IO*)
 * @param state - current game state holder (uint8_t*)
 */
void menu(GUI *gui, IO *io, uint8_t *state);

/*
 * Function holding play menu game state.
 *
 * @param gui   - associated graphical user interface (GUI*)
 * @param io    - associated input/output manager (IO*)
 * @param state - current game state holder (uint8_t*)
 * @param level - current level element (Level*) 
 */
void play(GUI *gui, IO *io, uint8_t *state, Level *level);

/*
 * Function holding direct playing state.
 *
 * @param gui   - associated graphical user interface (GUI*)
 * @param io    - associated input/output manager (IO*)
 * @param state - current game state holder (uint8_t*)
 * @param level - current level element (Level*) 
 */
void game(GUI *gui, IO *io, uint8_t *state, Level *level);

/*
 * Function holding score screen game state.
 *
 * @param gui   - associated graphical user interface (GUI*)
 * @param io    - associated input/output manager (IO*)
 * @param state - current game state holder (uint8_t*)
 * @param level - current level element (Level*) 
 */
void score(GUI *gui, IO *io, uint8_t *state, Level *level);

#endif // __STATES_H__
