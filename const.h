/*******************************************************************
  Constants using in Breaks Braker game.

  const.c      - usable constants

  (C) Copyright 2023 by Artem Liamkin
      e-mail:   artemlyamkin@yahoo.com
      license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef __CONST_H__
#define __CONST_H__

// -----------------------------------------------------------------------------
// CONSTANTS
// -----------------------------------------------------------------------------
#define NL                      0x0A
#define LOADTIME                500000
#define BLINKTIME               200000   



// -----------------------------------------------------------------------------
//    LOG
// -----------------------------------------------------------------------------
#define LOG_BACKGROUND          "[LOG] Background images were loaded.\n"
#define LOG_BUTTON              "[LOG] Button images were loaded.\n"
#define LOG_DIGIT               "[LOG] Digit images were loaded.\n"
#define LOG_BRICK               "[LOG] Brick images were loaded.\n"
#define LOG_PLATFORM            "[LOG] Platform image was loaded.\n"
#define LOG_BALL                "[LOG] Ball image was loaded.\n"
#define LOG_LEVEL               "[LOG] Loaded level %d with speed %d.\n"
#define LOG_WIN                 "[LOG] Level completed. Score: %d.\n"
#define LOG_LOSE                "[LOG] Level failed. Score: %d.\n"

// -----------------------------------------------------------------------------
//       ERROR
// -----------------------------------------------------------------------------
#define LOG_ERROR_BACKGROUND    "[ERROR] Can't find backgrounds file!\n"
#define LOG_ERROR_BUTTON        "[ERROR] Can't find buttons file!\n"
#define LOG_ERROR_DIGIT         "[ERROR] Can't find digits file!\n"
#define LOG_ERROR_BRICK         "[ERROR] Can't find bricks file!\n"
#define LOG_ERROR_PLATFORM      "[ERROR] Can't find platform file!\n"
#define LOG_ERROR_BALL          "[ERROR] Can't find ball file!\n"
#define LOG_ERROR_LEVEL         "[ERROR] Can't find level file!\n"
#define LOG_ERROR_MALLOC        "[ERROR] Can't allocate memory!\n"



// -----------------------------------------------------------------------------
//    STATES
// -----------------------------------------------------------------------------
#define STATE_MENU              0
#define STATE_PLAY              1
#define STATE_GAME              2
#define STATE_SCORE             3
#define STATE_EXIT              4



// -----------------------------------------------------------------------------
//    LEVEL
// -----------------------------------------------------------------------------
#define LEVEL_1                 "/tmp/liamkart/res/lvl/1.bin" // for use without chdir
#define LEVEL_2                 "/tmp/liamkart/res/lvl/2.bin" // for use without chdir
#define LEVEL_3                 "/tmp/liamkart/res/lvl/3.bin" // for use without chdir
#define LEVEL_4                 "/tmp/liamkart/res/lvl/4.bin" // for use without chdir
#define LEVEL_5                 "/tmp/liamkart/res/lvl/5.bin" // for use without chdir
// #define LEVEL_1                 "res/lvl/1.bin"               // for use with chdir
// #define LEVEL_2                 "res/lvl/2.bin"               // for use with chdir
// #define LEVEL_3                 "res/lvl/3.bin"               // for use with chdir
// #define LEVEL_4                 "res/lvl/4.bin"               // for use with chdir
// #define LEVEL_5                 "res/lvl/5.bin"               // for use with chdir
#define LEVEL_1_BRICKS          170
#define LEVEL_2_BRICKS          240
#define LEVEL_3_BRICKS          174
#define LEVEL_4_BRICKS          171
#define LEVEL_5_BRICKS          128

// -----------------------------------------------------------------------------
//         PLAYER
// -----------------------------------------------------------------------------
#define LEVEL_PLAYER_STEP       GUI_GAMEPIX_W
#define LEVEL_PLAYER_LIMIT_L    LEVEL_PLAYER_STEP
#define LEVEL_PLAYER_LIMIT_R    GUI_W - GUI_PLATFORM_W - LEVEL_PLAYER_STEP



// -----------------------------------------------------------------------------
//    IO
// -----------------------------------------------------------------------------
#define IO_BUTTON               0x2000000
#define IO_VALUE                0xFF00
#define IO_RIGHT                1
#define IO_LEFT                 2
#define IO_LIVES_3              0xFF0FF0FF
#define IO_LIVES_2              0xFF0FF
#define IO_LIVES_1              0xFF
#define IO_LIVES_0              0x0
#define IO_RGB_RED              0x550003
#define IO_RGB_GREEN            0x3303
#define IO_RGB_OFF              0x0



// -----------------------------------------------------------------------------
//    GUI
// -----------------------------------------------------------------------------
#define GUI_BACKGROUND          "/tmp/liamkart/res/backgrounds.ppm" // for use without chdir
#define GUI_BUTTON              "/tmp/liamkart/res/buttons.ppm"     // for use without chdir
#define GUI_DIGIT               "/tmp/liamkart/res/digits.ppm"      // for use without chdir
#define GUI_BRICK               "/tmp/liamkart/res/bricks.ppm"      // for use without chdir
#define GUI_PLATFORM            "/tmp/liamkart/res/platform.ppm"    // for use without chdir
#define GUI_BALL                "/tmp/liamkart/res/ball.ppm"        // for use without chdir
// #define GUI_BACKGROUND          "res/backgrounds.ppm"               // for use with chdir
// #define GUI_BUTTON              "res/buttons.ppm"                   // for use with chdir
// #define GUI_DIGIT               "res/digits.ppm"                    // for use with chdir
// #define GUI_BRICK               "res/bricks.ppm"                    // for use with chdir
// #define GUI_PLATFORM            "res/platform.ppm"                  // for use with chdir
// #define GUI_BALL                "res/ball.ppm"                      // for use with chdir
#define GUI_W                   480
#define GUI_H                   320
#define GUI_GAMEPIX_COUNT       20
#define GUI_GAMEPIX_W           24
#define GUI_GAMEPIX_H           16

// -----------------------------------------------------------------------------
//       BACKGROUND
// -----------------------------------------------------------------------------
#define GUI_BACKGROUND_BLANK    0
#define GUI_BACKGROUND_MAIN     1
#define GUI_BACKGROUND_WIN      2
#define GUI_BACKGROUND_LOSE     3
#define GUI_BACKGROUND_COUNT    4
#define GUI_BACKGROUND_W        GUI_GAMEPIX_W * GUI_GAMEPIX_COUNT
#define GUI_BACKGROUND_H        GUI_GAMEPIX_H * GUI_GAMEPIX_COUNT

// -----------------------------------------------------------------------------
//       BUTTON
// -----------------------------------------------------------------------------
#define GUI_BUTTON_PLAY         0
#define GUI_BUTTON_START        1
#define GUI_BUTTON_LEVEL        2
#define GUI_BUTTON_SPEED        3
#define GUI_BUTTON_BACK         4
#define GUI_BUTTON_QUIT         5
#define GUI_BUTTON_COUNT        6
#define GUI_BUTTON_W            GUI_GAMEPIX_W * 10
#define GUI_BUTTON_H            GUI_GAMEPIX_H * 3
#define GUI_BUTTON_X            GUI_GAMEPIX_W * 5
#define GUI_BUTTON_Y1           GUI_GAMEPIX_H * 3
#define GUI_BUTTON_Y2           GUI_GAMEPIX_H * 7
#define GUI_BUTTON_Y3           GUI_GAMEPIX_H * 11
#define GUI_BUTTON_Y4           GUI_GAMEPIX_H * 15

// -----------------------------------------------------------------------------
//       DIGIT
// -----------------------------------------------------------------------------
#define GUI_DIGIT_0             0
#define GUI_DIGIT_1             1
#define GUI_DIGIT_2             2
#define GUI_DIGIT_3             3
#define GUI_DIGIT_4             4
#define GUI_DIGIT_5             5
#define GUI_DIGIT_6             6
#define GUI_DIGIT_7             7
#define GUI_DIGIT_8             8
#define GUI_DIGIT_9             9
#define GUI_DIGIT_COUNT         10
#define GUI_DIGIT_W             14
#define GUI_DIGIT_H             GUI_GAMEPIX_H * 3
#define GUI_DIGIT_X1            280
#define GUI_DIGIT_X2            165
#define GUI_DIGIT_Y1            112
#define GUI_DIGIT_Y2            185

// -----------------------------------------------------------------------------
//       BRICK
// -----------------------------------------------------------------------------
#define GUI_BRICK_EMPTY         0
#define GUI_BRICK_EASY          1
#define GUI_BRICK_MED           2
#define GUI_BRICK_HARD          3
#define GUI_BRICK_COUNT         4
#define GUI_BRICK_W             GUI_GAMEPIX_W
#define GUI_BRICK_H             GUI_GAMEPIX_H

// -----------------------------------------------------------------------------
//       PLATFORM
// -----------------------------------------------------------------------------
#define GUI_PLATFORM_W          GUI_GAMEPIX_W * 4
#define GUI_PLATFORM_H          GUI_GAMEPIX_H
#define GUI_PLATFORM_X          8* GUI_GAMEPIX_W
#define GUI_PLATFORM_Y          (GUI_GAMEPIX_COUNT - 1) * GUI_GAMEPIX_H

// -----------------------------------------------------------------------------
//       BALL
// -----------------------------------------------------------------------------
#define GUI_BALL_W              12
#define GUI_BALL_H              12

#endif // __CONST_H__
