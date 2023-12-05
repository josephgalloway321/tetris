#include <iostream>
#include <raylib.h>
#include "../header/game.hpp"

int main()
{
  // Game Definitions & Initializations
  InitWindow(300, 600, "Tetris");
  SetTargetFPS(60);

  // Create game objects
  Game game;

  // Game loop
  while (WindowShouldClose() == false) {
    // Event handling
    game.handle_input();
    
    // Update

    // Draw
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);
    
    game.draw();

    EndDrawing();
  }

  CloseWindow();
}