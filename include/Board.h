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

#include "Player.h"

#ifndef _BOARD_H
#define _BOARD_H

class Board
{
public:
    int width;
    int height;
    Player **pieceMatrix;
    int connectN;

    Board(int connectN, int width, int height);

    /**
     * @param column
     */
    bool isPieceBelow(int column);

    /**
     * @param column
     */
    bool dropBelow(int column, Player *player);

    void reset();
    /**
     * @param player
     */
    bool checkWin(Player *player);

private:
    bool checkWinWithDirection(Player *player, int deltaY, int deltaX);
    bool checkWinAtLocation(Player *player, int deltaY, int deltaX, int row, int col);
};

#endif //_BOARD_H