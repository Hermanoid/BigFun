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
    start_color();
    int row, col;
    getmaxyx(stdscr, row, col);

    int boardXOffset = 0;
    int boardHeight, requiredHeight, width;
    boardHeight = board.height * 2 + 1;
    requiredHeight = boardHeight + 2; // Add two rows for status + selector rows
    width = board.width * 2 + 1;
    cout << "Width: " << width << "Cols: " << col << endl;
    if (row < requiredHeight || col < width)
    {
        // This function can behave pretty oddly if the terminal is too small to fit this size.
        // It's very unlikely that someone's screen will be <43 chars tall (the height with the max board height of 20),
        // so we'll (silently) leave it to the user to resize their screen if they see eratic behavior.
        resizeterm(max(requiredHeight, row), max(col, width));
    }
    // boardXOffset = (col - width) / 2;

    // newwin(rows, cols, y_start, x_start)
    // bannerWindow = newwin(1, col, 0, 0);
    // selectorWindow = newwin(1, width, 1, boardXOffset);
    // boardWindow = newwin(boardHeight, width, 2, boardXOffset);

    // wrefresh(bannerWindow);
    // wrefresh(selectorWindow);
    // wrefresh(boardWindow); /* Show that box 		*/
    refresh();
}

int printCentered(WINDOW *window, int y, string text)
{
    auto str = text.substr(0, min((int)text.size(), getmaxx(stdscr))).c_str();
    mvwprintw(window, y, centeredX(text.size()), str);
}

void DisplayManager::printBoard(int startRow, Board board)
{
    const int width = board.height * 2 + 1;
    const int height = board.width * 2 + 1;
    int row, col = 0;
    WINDOW *destWindow = stdscr;
    int startCol = centeredX(width);

    for (row = startRow; row < height + startRow; row++)
    {
        // Bring the cursor back to the start of the current row like a typewriter
        move(row, 0);
        for (col = startCol; col < width + startCol; col++)
        {
            const bool isTop = row == 0;
            const bool isBottom = row == height - 1;
            const bool isLeft = col == 0;
            const bool isRight = col == width - 1;
            const bool evenRow = row % 2 == 0;
            const bool evenCol = col % 2 == 0;
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
            else if (evenRow && evenCol)
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
            else if (evenRow && !evenCol)
            {
                waddch(destWindow, ACS_HLINE);
            }
            else if (!evenRow && evenCol)
            {
                waddch(destWindow, ACS_VLINE);
            }
            // pieces
            else
            {
                board.pieceMatrix[(row / 2) * board.width + (col / 2)]->symbol->renderCharacter(destWindow);
            }
        }
    }
}

void DisplayManager::printSelector(int row, Board board, Player *player, int currentColumn)
{
    int startX = centeredX(board.width * 2 + 1);
    for (int boardCol = startX; boardCol < board.width + startX; boardCol++)
    {
        move(row, (boardCol)*2 + 1);
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
    cout << "starting the good stuff" << endl;
    clear();
    printCentered(stdscr, 0, "It's " + player->name + "'s Turn. Controls: Arrow Keys (move and drop), Q (quit)");
    // wrefresh(bannerWindow);
    // printBoard(2, board);
    refresh();
    // cout << "printed board" << endl;
    int currentColumn = board.width / 2;
    while (true)
    {
        // "Hey I exist");
        printSelector(1, board, player, currentColumn);
        refresh();
        int input = wgetch(stdscr);
        cout << input << endl;
        switch (input)
        {
        case (int)'q':
            cout << "drop was quit" << endl;
            return -1;
        case KEY_LEFT:
            currentColumn = max(currentColumn - 1, 0);
            break;
        case KEY_RIGHT:
            currentColumn = min(currentColumn + 1, board.width - 1);
            break;
        case KEY_DOWN:
            cout << "Returning drop" << endl;
            return currentColumn;
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
    curs_set(1);
    clear();
    endwin();
}