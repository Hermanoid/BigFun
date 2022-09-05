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
#include <vector>

#ifndef _SAVEDATA_H
#define _SAVEDATA_H

class SaveData
{
public:
    int allTimeGamesPlayed;
    std::vector<Player> players;
};

#endif //_SAVEDATA_H