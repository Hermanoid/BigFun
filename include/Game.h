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
#include "Board.h"

#ifndef _GAME_H
#define _GAME_H

class Game
{
public:
    Game(Board board, Player **players, int numPlayers);
    Game(Board board, Player **players, int numPlayers, bool quickPlay);
    Board board;
    Player **players;
    Player *winner;
    int numPlayers;
    /// @brief quickPlay games are played with Guests and should not be saved
    bool quickPlay;

    void reset();
};

#endif //_GAME_H