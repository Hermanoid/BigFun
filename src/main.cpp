#include <iostream>
#include "GameManager.h"
#include <sstream>

using namespace std;

int main()
{
    GameManager gm("gamesave.json");
    gm.play();
    return 0;
}