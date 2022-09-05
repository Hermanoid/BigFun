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

#ifndef _INTERACTIVEHELPERS_H
#define _INTERACTIVEHELPERS_H

#include <functional>
#include <iostream>

using namespace std;

class InteractiveHelpers
{
public:
    static bool isNumber(const string &str);
    static bool validBoolInput(string prompt);
    static int validIntInputWithDefault(string prompt, int default_, std::function<bool(int)> validate);
};

#endif // _INTERACTIVEHELPERS_H