#include <iostream>
#include <raylib.h>
#include "../header/game.hpp"

const float BLOCK_FALL_SPEED = 0.2;  // seconds

// TODO: Move to a function in another file
// Keep track of time when last update occurred
double last_update_time = 0;

bool event_triggered(double interval) {
  double current_time = GetTime();
  if(current_time - last_update_time >= interval) {
    last_update_time = current_time;
    return true;
  }
  return false;
}

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
    
    // If true, then interval has passed
    if (event_triggered(BLOCK_FALL_SPEED)) {
      game.move_block_down();
    }
    
    // Update

    // Draw
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);
    
    game.draw();

    EndDrawing();
  }

  CloseWindow();
}