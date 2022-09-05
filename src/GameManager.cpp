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

GameManager::GameManager(string jsonPath)
{
    this->jsonPath = jsonPath;
    // this->saveManager = SaveManager();
    this->displayManager = DisplayManager();
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
    Game game = GameSetup::interactiveSetup();

    stringstream ss("");
    for (int i = 0; i < game.numPlayers; i++)
    {
        if (i != 0)
        {
            if (i == game.numPlayers - 1)
            {
                ss << " and ";
            }
            else
            {
                ss << ", ";
            }
        }
        ss << game.players[i]->name;
    }

    bool playAgain = false;
    do
    {
        cout << endl;
        cout << "****************************************************************************" << endl;
        cout << "Playing a new game with " << ss.str() << ". Connect-N: " << game.board.connectN << " Width: " << game.board.width << " Height: " << game.board.height << endl
             << endl;
        cout << "****************************************************************************" << endl;

        doGame(&game);
        printOutcome(game);
        playAgain = InteractiveHelpers::validBoolInput("Would you like to play again?");
        if (playAgain)
        {
            game.reset();
        }
    } while (playAgain);

    cout << endl;
    cout << "You played a game! Wasn't it awesome?" << endl;
}

/**
 * @param game
 * @return void
 */
void GameManager::doGame(Game *game)
{
    displayManager.begin(game->board);
    bool gameWon = false;
    int playerIndex = 0;
    while (!gameWon)
    {
        Player *player = game->players[playerIndex];
        gameWon = doTurn(game->board, player);
        if (gameWon)
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
bool GameManager::doTurn(Board board, Player *player)
{
    cout << "Doing a turn..." << endl;
    int dropColumn = displayManager.getDrop(board, player);
    if (!board.dropBelow(dropColumn, player))
    {
        cout << "This error should not occur: the player's piece could not be dropped in the specified column" << endl;
    }
    return board.checkWin(player);
}

/**
 * @param game
 * @return void
 */
void GameManager::printOutcome(Game game)
{
    cout << game.winner->name << " Wins!!" << endl;
}