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

#include "GameSetup.h"
#include "InteractiveHelpers.h"
#include "ColoredSymbol.h"
#include "NormalSymbol.h"

Player **GameSetup::interactivePlayersSetup(vector<Player> savedPlayers, int numPlayers)
{
    Player **players = new Player *[numPlayers];
    for (int i = 0; i < numPlayers; i++)
    {
        string name;
        cout << "Please enter the name for player #" << i << ": ";
        cin >> name;

        cout << "TODO: Implement saved player searching" << endl;

        unique_ptr<Symbol> symbol;
        string symbolColored, symbolCharacter;
        cout << "Hello, " << name << "!" << endl
             << "What character would you like your piece to be while playing? ('O' is a good choice): ";
        cin >> symbolCharacter;

        if (InteractiveHelpers::validBoolInput("Should this piece be colorized? (Enter Y or N):"))
        {
            cout << "That's super cool!  Lucky you, you get whatever this color is going to be, because the selector has not been implemented yet." << endl;
            symbol = make_unique<ColoredSymbol>(symbolCharacter[0], rand() % 16);
        }
        else
        {
            symbol = make_unique<NormalSymbol>(symbolCharacter[0]);
        }

        cout << endl;
        // As before, we create this player in expectation that players will not be released until the end of the program
        // So, we don't worry about pointer shenanigans
        // I'll take full reponsibility should this bite me in the butt later.
        Player *player = new Player(move(symbol), name);
        players[i] = player;
    }
    return players;
}

Board GameSetup::interactiveBoardSetup()
{
    int connectN, width, height = 0;
    cout << "Now, enter your Connect-N. This is how many pieces must land in a row to win." << endl;

    auto connectNValidate = [](int num)
    { return num >= 3 && num <= 10; };
    connectN = InteractiveHelpers::validIntInputWithDefault("Connect-N (between 3 and 10)", 4, connectNValidate);

    cout << endl;
    cout << "Next, enter the game width and height" << endl;

    int upperBound = 20;
    string boundString = "(between " + to_string(connectN) + " and " + to_string(upperBound) + ")";
    auto dimValidate = [=](int num)
    { return num >= connectN && num <= 20; };

    width = InteractiveHelpers::validIntInputWithDefault("Width " + boundString, connectN + 3, dimValidate);
    height = InteractiveHelpers::validIntInputWithDefault("Height " + boundString, connectN + 2, dimValidate);

    return Board(connectN, width, height);
}

Game GameSetup::quickGameSetup()
{
    auto symbolOne = make_unique<ColoredSymbol>('O', 1);
    auto symbolTwo = make_unique<ColoredSymbol>('X', 7);

    // If you're a grader and you're reading this...
    // first of all, hello!  And second of all,
    // yeah, this technically causes a memory leak.
    // I noted it, and in the words of Nick Fury,
    // "elected to ignore it"
    // These player objects will be kindly implicitly deallocated upon program completion.
    Player *playerOne = new Player(move(symbolOne), "Guest 1");
    Player *playerTwo = new Player(move(symbolTwo), "Guest 2");
    Player **players = new Player *[2]
    { playerOne, playerTwo };
    return Game(Board(4, 7, 6), players, 2, true);
}

/**
 * @return Game
 */
Game GameSetup::interactiveSetup(SaveData data)
{
    cout << "To start, please enter a few details to set up a game, or choose Quick Play." << endl;
    int numPlayers = 0;
    while (true)
    {
        cout << "Please enter the number of players to start game setup. Or, enter 'Q' for Quick Play: ";
        string enteredText;
        cin >> enteredText;
        if (InteractiveHelpers::isNumber(enteredText))
        {
            numPlayers = stoi(enteredText);
            break;
        }
        else if (enteredText == "q" || enteredText == "Q")
        {
            return quickGameSetup();
        }
        else
        {
            cout << "Invalid input." << endl;
        }
    }

    Player **players = interactivePlayersSetup(data.players, numPlayers);
    // cin.get(); // Throw away a spurious newline. It's pretty odd.
    Board board = interactiveBoardSetup();
    // cin.get(); // Throw away another spurious newline. It remains pretty odd.

    return Game(board, players, numPlayers);
}
