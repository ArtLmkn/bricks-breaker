/*******************************************************************
  Bricks Breaker game for MZAPO kit.

  main.c      - Bricks Breaker entry point

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "imports.h"



void clean(GUI *gui, IO *io) {
    if (gui && gui->frameBuffer) free(gui->frameBuffer);

    // LCD clearing
    parlcd_write_cmd(io->lcd, 0x2c);
    for (int i = 0; i < GUI_W * GUI_H; ++i) parlcd_write_data(io->lcd, 0u);
}



int main(int argc, char **argv) {
    // Changing program directory (to use filenames without full path)
    // char *baseDir;
    // const char *p = strrchr(argv[0], '/');
    // if (!p) baseDir = "."; else baseDir = strndup(argv[0], p - argv[0]);
    // chdir(baseDir);

    // Start initialisations
    uint8_t state = STATE_MENU;
    GUI gui = initGUI(&state);
    IO io = initIO();
    Level level = initLevel();

    // Gameloop
    while (true) {
      if (state == STATE_MENU) menu(&gui, &io, &state);
      else if (state == STATE_PLAY) play(&gui, &io, &state, &level);
      else if (state == STATE_GAME) game(&gui, &io, &state, &level);
      else if (state == STATE_SCORE) score(&gui, &io, &state, &level);
      else if (state == STATE_EXIT) break;
    }

    clean(&gui, &io); // Final cleaning    

    return 0;
}
