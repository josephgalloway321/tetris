#include <iostream>
#include <raylib.h>
#include "../header/grid.hpp"
#include "../header/colors.hpp"

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
    ClearBackground(CUSTOM_DARK_BLUE);

    grid.draw();

    EndDrawing();
  }

  CloseWindow();
}