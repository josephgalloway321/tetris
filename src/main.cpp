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

  // TEST Images
  Image image = LoadImage("C:/Users/josep/Documents/GitHub/tetris/resources/images/volume.png");
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);
  //Texture2D texture = LoadTexture("C:/Users/josep/Pictures/remi_edit.jpg");
  
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
    DrawTextEx(FONT, "High Score", {325, 20}, 32, 2, WHITE);
    DrawRectangleRounded({320, 70, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    DrawTextEx(FONT, "Score", {360, 150}, 32, 2, WHITE);
    DrawRectangleRounded({320, 200, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    DrawTextEx(FONT, "Next", {370, 280}, 32, 2, WHITE);
    DrawRectangleRounded({320, 330, 170, 180}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    if(game.is_game_over()) {
      //DrawTextEx(FONT, "Game Over", {320, 450}, 38, 2, RED);
    }

    // Print score & high score logic, used for centering objects in boxes
    char score_text[10];
    sprintf(score_text, "%d", game.get_score());  // Change int to text
    Vector2 score_text_size = MeasureTextEx(FONT, score_text, 32, 2);
    DrawTextEx(FONT, score_text, {320 + (170 - score_text_size.x)/2, 215}, 32, 2, WHITE);
    char high_score_text[10];
    sprintf(high_score_text, "%d", game.get_high_score());  // Change int to text
    Vector2 high_score_text_size = MeasureTextEx(FONT, high_score_text, 32, 2);
    DrawTextEx(FONT, high_score_text, {320 + (170 - high_score_text_size.x)/2, 85}, 32, 2, WHITE);

    game.draw();
    

    // TEST Draw volume image
    DrawTexture(texture, 420, 550, BLACK);

    EndDrawing();
  }

  CloseWindow();
}