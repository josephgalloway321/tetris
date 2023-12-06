#include <iostream>
#include <raylib.h>
#include "../header/game.hpp"
#include "../header/event_timers.hpp"

int main()
{
  // Game Definitions & Initializations
  InitWindow(500, 620, "Tetris");
  SetTargetFPS(60);

  // CONSTANTS
  const Font FONT = LoadFontEx("../resources/font/monogram.ttf", 64, 0, 0);
  const double BLOCK_FALL_SPEED = 0.2;  // seconds

  // Create game objects
  Game game;
  Timer block_fall_speed_timer;
  
  // Game loop
  while (WindowShouldClose() == false) {
    /*
    * Event handling
    */
    // Handle user input
    game.handle_input();

    // Handle time passed to regulate block falling speed
    if(block_fall_speed_timer.elapsed() > BLOCK_FALL_SPEED) {
      game.move_block_down();
      block_fall_speed_timer.reset_timer();
    }
    
    /*
    * Update
    */
    // Update background music
    UpdateMusicStream(game.music);

    /*
    *  Draw
    */
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);
    
    // User interface
    DrawTextEx(FONT, "Score", {365, 15}, 38, 2, WHITE);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    DrawTextEx(FONT, "Next", {370, 175}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    if(game.game_over) {
      DrawTextEx(FONT, "Game Over", {320, 450}, 38, 2, RED);
    }

    // Printing score logic, used for centering objects in box
    char score_text[10];
    sprintf(score_text, "%d", game.score);  // Change int to text
    Vector2 text_size = MeasureTextEx(FONT, score_text, 38, 2);
    DrawTextEx(FONT, score_text, {320 + (170 - text_size.x)/2, 65}, 38, 2, WHITE);

    game.draw();

    EndDrawing();
  }

  CloseWindow();
}