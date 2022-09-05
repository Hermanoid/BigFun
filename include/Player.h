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

#include "Symbol.h"
#include <memory>
#include <string>

#ifndef _PLAYER_H
#define _PLAYER_H

using namespace std;

class Player
{
public:
    Player(const Player &old);
    Player(shared_ptr<Symbol> symbol, string name);
    Player(shared_ptr<Symbol> symbol, string name, int wins, int losses);
    shared_ptr<Symbol> symbol;
    string name;
    int wins;
    int losses;
};

#endif //_PLAYER_H