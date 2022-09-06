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

#include "GameManager.h"
#include "ColoredSymbol.h"
#include "NormalSymbol.h"
#include "InteractiveHelpers.h"
#include "GameSetup.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * GameManager implementation
 */

GameManager::GameManager(string jsonPath) : saveManager(jsonPath), jsonPath(jsonPath)
{
}
string combinePlayerNames(Player **players, int numPlayers)
{
    stringstream ss("");
    for (int i = 0; i < numPlayers; i++)
    {
        if (i != 0)
        {
            if (i == numPlayers - 1)
            {
                ss << " and ";
            }
            else
            {
                ss << ", ";
            }
        }
        ss << players[i]->name;
    }
    return ss.str();
}

/**
 * @return void
 */
void GameManager::play()
{
    cout << "****************************************************************************" << endl;
    cout << "Welcome to BIG FUN, the Beguiling Interactive Game For Unraveling Connect-N!" << endl;
    cout << "****************************************************************************" << endl;
    cout << endl;
    saveManager.loadData();
    Game game = GameSetup::interactiveSetup(saveManager);
    saveManager.printStats(game.players, game.numPlayers);
    auto playerString = combinePlayerNames(game.players, game.numPlayers);

    bool playAgain = false;
    do
    {
        cout << endl;
        cout << "****************************************************************************" << endl;
        cout << "Playing a new game with " << playerString << ". Connect-N: " << game.board.connectN << " Width: " << game.board.width << " Height: " << game.board.height << endl;
        cout << "****************************************************************************" << endl;

        doGame(&game);
        saveManager.updateStatsWithGame(game);
        printOutcome(game);
        playAgain = InteractiveHelpers::validBoolInput("Would you like to play again?");
        if (playAgain)
        {
            game.reset();
        }
    } while (playAgain);
    saveManager.saveData();
    cout << endl;
    if (!game.quickPlay)
    {
        saveManager.printStats(game.players, game.numPlayers);
    }
    cout << endl;
    cout << "Thanks for playing!" << endl;
}

/**
 * @param game
 * @return void
 */
void GameManager::doGame(Game *game)
{
    displayManager.begin(game->board);
    TurnResult turnResult = TurnResult::nextTurn;
    int playerIndex = 0;
    while (turnResult == TurnResult::nextTurn)
    {
        Player *player = game->players[playerIndex];
        turnResult = doTurn(game->board, player);
        if (turnResult == TurnResult::gameWon)
        {
            game->winner = player;
        }
        playerIndex = (playerIndex + 1) % game->numPlayers;
    }
    displayManager.end();
}

/**
 * @param board
 * @param player
 * @return bool
 */
GameManager::TurnResult GameManager::doTurn(Board board, Player *player)
{
    int dropColumn = displayManager.getDrop(board, player);
    if (dropColumn == -1)
    {
        return TurnResult::gameQuit;
    }
    if (!board.dropBelow(dropColumn, player))
    {
        cout << "This error should not occur: the player's piece could not be dropped in the specified column" << endl;
    }
    return board.checkWin(player) ? TurnResult::gameWon : TurnResult::nextTurn;
}

/**
 * @param game
 * @return void
 */
void GameManager::printOutcome(Game game)
{
    if (game.winner == NULL)
    {
        cout << "This game ended with no winner!" << endl;
    }
    else
    {
        cout << game.winner->name << " Wins!!" << endl;
    }
}