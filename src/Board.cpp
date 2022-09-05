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

/**
 * Board implementation
 */

Board::Board(int connectN, int width, int height) : connectN(connectN), width(width), height(height)
{
    pieceMatrix = new Player *[width * height];
}

/**
 * @param column
 * @return bool is this column blocked/full? If this returns false, dropBelow() can be called to put a piece in this column.
 */
bool Board::isPieceBelow(int column)
{
    return false;
}

/**
 * @param column
 * @return bool
 */
bool Board::dropBelow(int column, Player *player)
{
    // TODO: Implement
    return isPieceBelow(column);
}

/**
 * @param player
 * @return bool
 */
bool Board::checkWin(Player *player)
{
    return false;
}