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

#ifndef _COLOREDSYMBOL_H
#define _COLOREDSYMBOL_H

#include "Symbol.h"

class ColoredSymbol : public Symbol
{
public:
    ColoredSymbol(char character, int colorPair);
    char character;
    int colorPair;

    void renderCharacter(WINDOW *window);
};

#endif //_COLOREDSYMBOL_H