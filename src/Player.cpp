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
#include "NormalSymbol.h"

/**
 * Player implementation
 */
Player::Player(Player *old)
{
    symbol = old->symbol;
    name = old->name;
    wins = old->wins;
    losses = old->losses;
}
Player::Player(const Player *&old) : Player(*old){};
Player::Player() : Player(new NormalSymbol('?'), "<unset>"){};
Player::Player(Symbol *symbol, string name) : Player(symbol, name, 0, 0) {}
Player::Player(Symbol *symbol, string name, int wins, int losses) : symbol(symbol), name(name), wins(wins), losses(losses) {}