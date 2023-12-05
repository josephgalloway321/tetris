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
  InitWindow(500, 620, "Tetris");
  SetTargetFPS(60);

  // Load font
  Font font = LoadFontEx("../resources/monogram.ttf", 64, 0, 0);

  // Create game objects
  Game game;

  // Game loop
  while (WindowShouldClose() == false) {
    /*****************************************************/
    // Event handling
    game.handle_input();
    
    // If true, then interval has passed
    if (event_triggered(BLOCK_FALL_SPEED)) {
      game.move_block_down();
    }
    
    /*****************************************************/
    // Update

    /*****************************************************/
    // Draw
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);
    
    // User interface
    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    if(game.game_over) {
      DrawTextEx(font, "Game Over", {320, 450}, 38, 2, RED);
    }

    // Printing score logic
    char score_text[10];
    sprintf(score_text, "%d", game.score);  // Change int to text
    Vector2 text_size = MeasureTextEx(font, score_text, 38, 2);
    DrawTextEx(font, score_text, {320 + (170 - text_size.x)/2, 65}, 38, 2, WHITE);

    game.draw();

    EndDrawing();
  }

  CloseWindow();
}