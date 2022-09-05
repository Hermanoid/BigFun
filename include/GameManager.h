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

#include "SaveManager.h"
#include "DisplayManager.h"
#include "Game.h"
#include "Player.h"
#include "Board.h"

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

using namespace std;

class GameManager
{
public:
    GameManager(string jsonPath);
    string jsonPath;
    SaveManager saveManager;

    void play();

private:
    DisplayManager displayManager;

    /**
     * @param game
     */
    void doGame(Game *game);

    /**
     * @param board
     * @param player
     */
    enum TurnResult
    {
        nextTurn = 0,
        gameWon = 1,
        gameQuit = 2
    };
    TurnResult doTurn(Board board, Player *player);

    /**
     * @param game
     */
    void printOutcome(Game game);
};

#endif //_GAMEMANAGER_H