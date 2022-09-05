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

#include <iostream>
#include "DisplayManager.h"

/**
 * DisplayManager implementation
 */

int const DisplayManager::colors[] =
    {
        COLOR_BLACK,
        COLOR_RED,
        COLOR_YELLOW,
        COLOR_GREEN,
        COLOR_CYAN,
        COLOR_BLUE,
        COLOR_MAGENTA,
        COLOR_WHITE,
};

DisplayManager::DisplayManager()
{
    // Preset all foreground/background combinations to make handling colors easier
    for (int background = 0; background < numColors; background++)
    {
        for (int foreground = 0; foreground < numColors; foreground++)
        {
            init_pair(background * numColors + foreground, colors[foreground], colors[background]);
        }
    }
}

int centeredX(int objWidth)
{
    int col = getmaxx(stdscr);
    return max((int)(col - objWidth) / 2, 0);
}

/**
 * @return void
 */
void DisplayManager::begin(Board board)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    if (has_colors() == FALSE)
    {
        endwin();
        cout << "Your terminal does not support color\n";
    }
    // start_color(); // Color functionality has been disabled to prevent eratic behavior on windows, the current target platform (see README.md)
    int row, col;
    getmaxyx(stdscr, row, col);

    int boardXOffset = 0;
    int boardHeight, requiredHeight, width;
    boardHeight = board.height * 2 + 1;
    requiredHeight = boardHeight + 2; // Add two rows for status + selector rows
    width = board.width * 4 + 1;
    if (row < requiredHeight || col < width)
    {
        // This function can behave pretty oddly if the terminal is too small to fit this size.
        // It's very unlikely that someone's screen will be <43 chars tall (the height with the max board height of 20),
        // so we'll (silently) leave it to the user to resize their screen if they see eratic behavior.
        resizeterm(max(requiredHeight, row), max(col, width));
    }
    refresh();
}

int printCentered(WINDOW *window, int y, string text)
{
    auto str = text.substr(0, min((int)text.length(), getmaxx(stdscr)));
    mvwprintw(window, y, centeredX(text.size()), str.c_str());
}

void DisplayManager::printBoard(int startRow, Board board)
{
    const int width = board.width * 2 + 1;
    const int height = board.height * 2 + 1;
    int row, col = 0;
    WINDOW *destWindow = stdscr;
    // Actual width is wider than # of columns because player tiles are 3-wide to make the thing square.
    int startCol = centeredX(board.width * 4 + 1);
    for (row = 0; row < height + 0; row++)
    {
        // Bring the cursor back to the start of the current row like a typewriter
        move(row + startRow, startCol);
        for (col = 0; col < width; col++)
        {
            const bool isTop = row == 0;
            const bool isBottom = row == height - 1;
            const bool isLeft = col == 0;
            const bool isRight = col == width - 1;
            const bool isBorderRow = row % 2 == 0;
            const bool isBorderCol = col % 2 == 0;
            // corners
            if (isTop && isLeft)
            {
                waddch(destWindow, ACS_ULCORNER);
            }
            else if (isTop && isRight)
            {
                waddch(destWindow, ACS_URCORNER);
            }
            else if (isBottom && isLeft)
            {
                waddch(destWindow, ACS_LLCORNER);
            }
            else if (isBottom && isRight)
            {
                waddch(destWindow, ACS_LRCORNER);
            }
            //  joints
            else if (isBorderRow && isBorderCol)
            {
                if (isTop)
                {
                    waddch(destWindow, ACS_TTEE);
                }
                else if (isLeft)
                {
                    waddch(destWindow, ACS_LTEE);
                }
                else if (isRight)
                {
                    waddch(destWindow, ACS_RTEE);
                }
                else if (isBottom)
                {
                    waddch(destWindow, ACS_BTEE);
                }
                else
                {
                    waddch(destWindow, ACS_PLUS);
                }
            }
            // lines
            else if (isBorderRow && !isBorderCol)
            {
                for (int i = 0; i < 3; i++)
                {
                    waddch(destWindow, ACS_HLINE);
                }
                // waddch(destWindow, ACS_HLINE);
            }
            else if (!isBorderRow && isBorderCol)
            {
                waddch(destWindow, ACS_VLINE);
            }
            // pieces
            else
            {
                Player *player = board.pieceMatrix[(row / 2) * board.width + (col / 2)];
                if (player == NULL)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        waddch(destWindow, ' ');
                    }
                }
                else
                {
                    waddch(destWindow, ' ');
                    player->symbol->renderCharacter(destWindow);
                    waddch(destWindow, ' ');
                }
            }
        }
    }
}

void DisplayManager::printSelector(int row, Board board, Player *player, int currentColumn)
{
    int startX = centeredX(board.width * 4 + 1);
    for (int boardCol = 0; boardCol < board.width; boardCol++)
    {
        move(row, startX + (boardCol)*4 + 2);
        if (boardCol == currentColumn - 1)
        {
            addch(ACS_LARROW | COLOR_PAIR(2));
        }
        else if (boardCol == currentColumn)
        {
            player->symbol->renderCharacter(stdscr);
        }
        else if (boardCol == currentColumn + 1)
        {
            addch(ACS_RARROW | COLOR_PAIR(2));
        }
        else
        {
            addch(ACS_BULLET | COLOR_PAIR(2));
        }
    }
}

/**
 * @param board
 * @param player
 * @return int column, or -1 for "the player quit the game"
 */
int DisplayManager::getDrop(Board board, Player *player)
{
    attron(COLOR_PAIR(5));
    clear();
    printCentered(stdscr, 0, "It's " + player->name + "'s Turn. Controls: Arrow Keys/WASD (move and drop), Q (quit)");
    printBoard(2, board);
    refresh();
    int currentColumn = board.width / 2;
    while (true)
    {
        printSelector(1, board, player, currentColumn);
        refresh();
        int input = wgetch(stdscr);
        switch (input)
        {
        case (int)'q':
        case (int)'Q':
            return -1;
        case KEY_LEFT:
        case (int)'a':
        case (int)'A':
            currentColumn = max(currentColumn - 1, 0);
            break;
        case KEY_RIGHT:
        case (int)'d':
        case (int)'D':
            currentColumn = min(currentColumn + 1, board.width - 1);
            break;
        case KEY_DOWN:
        case (int)'s':
        case (int)'S':
            if (!board.isPieceBelow(currentColumn))
            {
                return currentColumn;
            }
        default:
            // Ignore invalid input
            break;
        }
    }
}

/**
 * @return void
 */
void DisplayManager::end()
{
    // delwin(bannerWindow);
    // delwin(boardWindow);
    // delwin(selectorWindow);
    // curs_set(1);
    // clear();
    endwin();
}