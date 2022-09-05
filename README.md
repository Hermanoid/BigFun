# Beguiling Interactive Game For Unraveling N-Connect (BIG FUN)

This project was designed as a challenge final project for CSCI 200: Programming Concepts
it implements a connect-N game with a command-line interface using the ncurses library,
and also features player and player stat persistence via a JSON file.

The game goes something like this: At the start of the game, the players are given a chance to enter their information. If they are recognized from past games, their account is loaded and their stats are displayed - otherwise, they set up as a new player. The players can then select the size of their game map - it’s Connect N, not Connect 4, after all. Finally, the players can duke it out in a battle of wits until the game detects a winner.


---

Build Instructions (windows):
1. Have MinGW installed (can run `g++ --version`)
2. Have CMake installed
3. `mkdir build; cd build`
4. `cmake -G "MinGW Makefiles" ../`
5. `mingw32-make.exe`