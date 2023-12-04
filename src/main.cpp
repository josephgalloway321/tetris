#include <iostream>
#include <raylib.h>

// Define colors
const Color DARK_BLUE = {44, 44, 127, 255};

int main()
{
  // Game Definitions & Initializations
  InitWindow(300, 600, "Tetris");
  SetTargetFPS(60);

  // Game loop
  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(DARK_BLUE);

    EndDrawing();
  }

  CloseWindow();
}