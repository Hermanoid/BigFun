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
#include <iostream>

/**
 * Board implementation
 */

Board::Board(int connectN, int width, int height) : connectN(connectN), width(width), height(height)
{
    pieceMatrix = new Player *[width * height]
    { NULL };
}

/**
 * @param column
 * @return bool is this column blocked/full? If this returns false, dropBelow() can be called to put a piece in this column.
 */
bool Board::isPieceBelow(int column)
{
    return pieceMatrix[column] != NULL;
}

/**
 * @param column
 * @return bool
 */
bool Board::dropBelow(int column, Player *player)
{
    for (int row = height - 1; row >= 0; row--)
    {
        int index = row * width + column;
        if (pieceMatrix[index] == NULL)
        {
            pieceMatrix[index] = player;
            return true;
        }
    }
    return false;
}

void Board::reset()
{
    delete pieceMatrix;
    pieceMatrix = new Player *[width * height]
    { NULL };
}

bool Board::checkWinAtLocation(Player *player, int deltaY, int deltaX, int row, int col)
{
    for (int count = 0; count < connectN; count++)
    {
        int index = (row + count * deltaY) * width + col + deltaX * count;
        if (pieceMatrix[index] != player)
        {
            return false;
        }
    }
    return true;
}

/// @brief
/// @param player
/// @param deltaY
/// @param deltaX
/// @return
bool Board::checkWinWithDirection(Player *player, int deltaY, int deltaX)
{
    int startRow = deltaY < 0 ? connectN - 1 : 0;
    int endRow = deltaY > 0 ? height - connectN : height - 1;
    int startCol = deltaX < 0 ? connectN - 1 : 0;
    int endCol = deltaX > 0 ? width - connectN : width - 1;

    for (int row = startRow; row <= endRow; row++)
    {
        for (int col = startCol; col <= endCol; col++)
        {
            if (checkWinAtLocation(player, deltaY, deltaX, row, col))
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @param player
 * @return bool
 */
bool Board::checkWin(Player *player)
{
    // Straight lines
    return checkWinWithDirection(player, 0, 1) ||
           checkWinWithDirection(player, 1, 0) ||
           // Diagonals
           checkWinWithDirection(player, 1, 1) ||
           checkWinWithDirection(player, 1, -1);
}