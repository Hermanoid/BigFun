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
#include "json/json.hpp"
#include <fstream>
#include "NormalSymbol.h"
#include "ColoredSymbol.h"
#include <iostream>

/**
 * SaveManager implementation
 */

using json = nlohmann::json;

SaveManager::SaveManager(string jsonPath) : jsonPath(jsonPath) {}

/**
 * @return void
 */
void SaveManager::loadData()
{
    // ifstream f(jsonPath);
    // json jobj = json::parse(f);
    // f.close();

    // data.allTimeGamesPlayed = jobj["allTimeGamesPlayed"];
    // int numSavedPlayers = jobj["players"].size();
    // data.players = vector<Player>(numSavedPlayers);
    // for (int i = 0; i < numSavedPlayers; i++)
    // {
    //     string name = jobj["players"][i]["name"];
    //     int wins = jobj["players"][i]["wins"];
    //     int losses = jobj["players"][i]["losses"];
    //     unique_ptr<Symbol> symbol;
    //     if (jobj["players"][i]["symbol"].contains("colorPair"))
    //     {
    //         symbol = make_unique<ColoredSymbol>(
    //             jobj["players"][i]["symbol"]["character"].get<char>(),
    //             jobj["players"][i]["symbol"]["colorPair"].get<int>());
    //     }
    //     else
    //     {
    //         symbol = make_unique<NormalSymbol>(
    //             jobj["players"][i]["symbol"]["character"].get<char>());
    //     }
    //     data.players[i] = Player(move(symbol), name, wins, losses);
    // }
}

void SaveManager::printStats(Player **players, int numPlayers)
{
    // cout << "All-time games played: " << data.allTimeGamesPlayed << endl;
    // for (int i = 0; i < numPlayers; i++)
    // {
    //     Player *player = players[i];
    //     cout << "Player: " << setw(20) << player->name << " has " << setw(4) << player->wins << " wins and " << setw(4) << player->losses << "losses!";
    //     cout << " W/L ratio: " << setprecision(3) << setw(6) << ((float)player->wins / player->losses);
    //     cout << endl;
    // }
    // return;
}

Player *SaveManager::findSavedPlayerByName(string name)
{
    // for (int i = 0; i < data.players.size(); i++)
    // {
    //     if (data.players[i].name == name)
    //     {
    //         return &(data.players[i]);
    //     }
    // }
    // return NULL;
    return NULL;
}

void updateWinStats(Player *player, Game game)
{
    if (game.winner->name == player->name)
    {
        player->wins++;
    }
    else
    {
        player->losses++;
    }
}

/**
 * @param game
 * @return void
 */
void SaveManager::updateStatsWithGame(Game game)
{
    // data.allTimeGamesPlayed++;
    // if (game.quickPlay)
    // {
    //     // Don't save stats for quickPlay games
    //     return;
    // }
    // for (int i = 0; i < game.numPlayers; i++)
    // {
    //     Player *playerResult = findSavedPlayerByName(game.players[i]->name);
    //     // If player does not already exist in saveData, add it
    //     if (playerResult == NULL)
    //     {
    //         updateWinStats(game.players[i], game);
    //         data.players.emplace_back(game.players[i]);
    //     }
    //     else
    //     {
    //         updateWinStats(playerResult, game);
    //     }
    // }
    return;
}

/**
 * @return void
 */
void SaveManager::saveData()
{
    // json jobj;

    // jobj["allTimeGamesPlayed"] = data.allTimeGamesPlayed;
    // for (int i = 0; i < data.players.size(); i++)
    // {
    //     Player *player = &(data.players[i]);
    //     jobj["players"][i]["name"] = player->name;
    //     jobj["players"][i]["wins"] = player->wins;
    //     jobj["players"][i]["losses"] = player->losses;
    //     if (NormalSymbol *v = dynamic_cast<NormalSymbol *>(data.players[i].symbol.get()))
    //     {
    //         jobj["players"][i]["symbol"]["character"] = v->character;
    //     }
    //     else if (ColoredSymbol *v = dynamic_cast<ColoredSymbol *>(data.players[i].symbol.get()))
    //     {
    //         jobj["players"][i]["symbol"]["character"] = v->character;
    //         jobj["players"][i]["symbol"]["colorPair"] = v->colorPair;
    //     }
    //     else
    //     {
    //         cout << "Failed to save: found an unexpected Symbol type" << endl;
    //     }
    // }
    // ofstream f(jsonPath);
    // f << jobj.dump();
    // f.close();
}