/**
 * CSCI 200: Final Project - Beguiling Interactive Game For Unraveling N-Connect (BIG FUN)
 *
 * Author: Lucas Niewohner
 *
 * This project was designed as a challenge final project for CSCI 200: Programming Concepts
 * it implements a connect-N game with a command-line interface using the ncurses library,
 * and also features player and player stat persistence via a JSON file.
 *
 */

#include "ColoredSymbol.h"

/**
 * ColoredSymbol implementation
 */

ColoredSymbol::ColoredSymbol(char character, int colorPair) : character(character), colorPair(colorPair) {}

/**
 * @return void
 */
void ColoredSymbol::renderCharacter(WINDOW *window)
{
    waddch(window, character | COLOR_PAIR(colorPair));
}