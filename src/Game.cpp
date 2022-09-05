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

#include "Game.h"

/**
 * Game implementation
 */

Game::Game(Board board, Player **players, int numPlayers, bool quickPlay) : board(board), players(players), numPlayers(numPlayers), winner(NULL){};
Game::Game(Board board, Player **players, int numPlayers) : Game(board, players, numPlayers, false){};

/**
 * @return void
 */
void Game::reset()
{
    this->winner = NULL;
    this->board.reset();
    return;
}