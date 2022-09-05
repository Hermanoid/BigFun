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

#include "SaveData.h"
#include "Player.h"
#include "Game.h"

#ifndef _SAVEMANAGER_H
#define _SAVEMANAGER_H

using namespace std;

class SaveManager
{
public:
    SaveData data;
    string jsonPath;

    SaveManager(string jsonPath);

    void loadData();

    /**
     * @param players
     * @param numPlayers
     */
    void printStats(Player **players, int numPlayers);

    /**
     * @param game
     */
    void updateStatsWithGame(Game game);

    void saveData();
    Player *findSavedPlayerByName(string name);
};

#endif //_SAVEMANAGER_H