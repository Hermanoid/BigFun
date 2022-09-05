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

#include "NormalSymbol.h"

/**
 * NormalSymbol implementation
 */
NormalSymbol::NormalSymbol(char character) : character(character){};

/**
 * @return void
 */
void NormalSymbol::renderCharacter(WINDOW *window)
{
    waddch(window, character);
}