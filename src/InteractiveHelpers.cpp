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
#include <string>

#include "InteractiveHelpers.h"

using namespace std;

bool InteractiveHelpers::isNumber(const string &str)
{
    for (char const &c : str)
    {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}

int InteractiveHelpers::validIntInputWithDefault(string prompt, int default_, std::function<bool(int)> validate)
{
    string entered_value;
    while (true)
    {
        cout << prompt << " (leave blank for the default, " << default_ << "): ";
        cin >> entered_value;
        if (entered_value == "")
        {
            return default_;
        }
        else if (isNumber(entered_value))
        {
            int number = stoi(entered_value);
            if (validate(number))
            {
                return number;
            }
        }
        cout << "Invalid input! Please try again." << endl;
    }
}

bool InteractiveHelpers::validBoolInput(string prompt)
{
    while (true)
    {
        cout << prompt << " (Enter Y or N): ";
        string entry;
        cin >> entry;
        if (entry == "y" || entry == "Y")
        {
            return true;
        }
        else if (entry == "n" || entry == "N")
        {
            return false;
        }
        else
        {
            cout << "Invalid input! Please try again" << endl;
        }
    }
}
