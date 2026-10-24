# Breakout

A Breakout clone written in C++ with raylib.

## Controls
- A / D: move the paddle
- R: restart after the game ends

## Rules
You have 3 lives. Destroy all the bricks with the ball to win.
Lose a life every time the ball falls below the paddle.

## Build
1. Install a MinGW-w64 compiler (e.g. the one that comes with the raylib installer).
2. Open the folder in VS Code.
3. Press `Ctrl+Shift+B` and choose "build debug".
4. Run `bin/Debug/breakout.exe`.

## What I learned
Second C++ project, coming from Unity/C#. Practiced `std::vector` and range-based
for loops to manage a variable number of bricks, structs with constructors,
passing by reference, and splitting game logic into functions.

## Credits
Built from the [raylib-quickstart](https://github.com/raylib-extras/raylib-quickstart) template.
