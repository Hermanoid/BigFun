# Beguiling Interactive Game For Unraveling N-Connect (BIG FUN)

This project was designed as a challenge final project for CSCI 200: Programming Concepts
it implements a connect-N game with a command-line interface using the ncurses library,
and also features player and player stat persistence via a JSON file.

The game goes something like this: At the start of the game, the players are given a chance to enter their information. If they are recognized from past games, their account is loaded and their stats are displayed - otherwise, they set up as a new player. The players can then select the size of their game map - it’s Connect N, not Connect 4, after all. Finally, the players can duke it out in a battle of wits until the game detects a winner.


---

Build Instructions (windows):
1. Have MinGW installed (can run `mingw32-make --version`)
2. Have CMake installed
3. Starting in this (project root directory), perform the following commands
4. `mkdir build; cd build`
5. `cmake -G "MinGW Makefiles" ../`
6. `mingw32-make.exe`

---
Known limitations:
1. The Ncurses library doesn't play nice with the windows color system. Additionally, more recent (and potentially color-compatible) versions of Ncurses fail to build on windows. Thus, the color features of this game only work on WSL or an actual linux machine. Because this project will only be used (and graded) on windows machines, color functionality has been disabled to prevent eratic behavior.
2. The ncurses library used also does not handle window resizing well; it's necessary to re-start the script to get window size information to update.
3. Ncurses plays especially poorly with Powershell. Use the usual windows command prompt.