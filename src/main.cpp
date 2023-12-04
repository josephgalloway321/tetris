#include <iostream>
#include <raylib.h>
#include "../header/grid.hpp"

// Define colors
const Color DARK_BLUE = {44, 44, 127, 255};

int main()
{
  // Game Definitions & Initializations
  InitWindow(300, 600, "Tetris");
  SetTargetFPS(60);

  // Create game objects
  Grid grid;
  grid.print();

  // Game loop
  while (WindowShouldClose() == false) {
    // Event handling
    
    // Update

    // Draw
    BeginDrawing();
    ClearBackground(DARK_BLUE);

    grid.draw();

    EndDrawing();
  }

  CloseWindow();
}