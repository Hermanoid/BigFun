#include <iostream>
#include "GameManager.h"
#include <sstream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    rand();
    GameManager gm("../gamesave.json");
    gm.play();
    return 0;
}