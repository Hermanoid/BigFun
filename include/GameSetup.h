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

#ifndef _GAMESETUP_H
#define _GAMESETUP_H

#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"

using namespace std;

class GameSetup
{
public:
    static Player **interactivePlayersSetup(int numPlayers);
    static Board interactiveBoardSetup();
    static Game quickGameSetup();
    static Game interactiveSetup();
};

#endif // _GAMESETUP_H