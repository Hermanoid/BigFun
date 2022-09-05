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

#include "Board.h"
#include "Player.h"
#include <ncursesw/ncurses.h>

#ifndef _DISPLAYMANAGER_H
#define _DISPLAYMANAGER_H

class DisplayManager
{
public:
    DisplayManager();
    void begin(Board board);

    /**
     * @param board
     * @param player
     */
    int getDrop(Board board, Player *player);
    void end();

    static const int numColors = 8;
    static const int colors[numColors];

private:
    void printBoard(int startrow, Board board);
    void printSelector(int row, Board board, Player *player, int currentColumn);
    // WINDOW *bannerWindow;
    // WINDOW *selectorWindow;
    // WINDOW *boardWindow;
};

#endif //_DISPLAYMANAGER_H