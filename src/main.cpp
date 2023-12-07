#include <iostream>
#include <raylib.h>
#include "../header/game.hpp"
#include "../header/event_timers.hpp"

const double BLOCK_FALL_SPEED = 0.2;  // seconds

int main()
{
  // Game Definitions & Initializations
  InitWindow(500, 620, "Tetris");
  SetTargetFPS(60);

  // Create game objects
  Game game;
  Timer block_fall_speed_timer;

  // TODO: Move sound toggle code to game.cpp within handle_input()
  // TEST FOR VOLUME BUTTON INTERACTION
  Rectangle btn_bounds = {385, 550, 50, 40};  // x, y, width, height
  int mute_toggle = 1;  // -1=Mute, 1=Unmute
  
  // Game loop
  while (WindowShouldClose() == false) {

    /***********************************
    * Event handling
    ***********************************/
    // Handle user input
    game.handle_input();

    // Handle time passed to regulate block falling speed
    if(block_fall_speed_timer.elapsed() > BLOCK_FALL_SPEED) {
      game.move_block_down();
      block_fall_speed_timer.reset_timer();
    }
    
    /***********************************
    * Update
    ***********************************/
    // Update background music
    UpdateMusicStream(game.music);

    // Get mouse position
    Vector2 mouse_position = GetMousePosition();

    /***********************************
    *  Draw
    ***********************************/
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);
    
    // User interface
    DrawTextEx(game.font, "High Score", {325, 20}, 32, 2, WHITE);
    DrawRectangleRounded({320, 70, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    DrawTextEx(game.font, "Score", {360, 150}, 32, 2, WHITE);
    DrawRectangleRounded({320, 200, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
    DrawTextEx(game.font, "Next", {370, 280}, 32, 2, WHITE);
    DrawRectangleRounded({320, 330, 170, 180}, 0.3, 6, CUSTOM_LIGHT_BLUE);

    if(game.is_game_over()) {
      //DrawTextEx(font, "Game Over", {320, 450}, 38, 2, RED);
    }

    // Print score & high score logic, used for centering objects in boxes
    char score_text[10];
    sprintf(score_text, "%d", game.get_score());  // Change int to text
    Vector2 score_text_size = MeasureTextEx(game.font, score_text, 32, 2);
    DrawTextEx(game.font, score_text, {320 + (170 - score_text_size.x)/2, 215}, 32, 2, WHITE);
    char high_score_text[10];
    sprintf(high_score_text, "%d", game.get_high_score());  // Change int to text
    Vector2 high_score_text_size = MeasureTextEx(game.font, high_score_text, 32, 2);
    DrawTextEx(game.font, high_score_text, {320 + (170 - high_score_text_size.x)/2, 85}, 32, 2, WHITE);

    // Draw game elements
    game.draw();

    // Highlight volume button when mouse hovers
    // Toggle volume on/off when clicked
    
    // Button clicked within bounds, toggle
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_position, btn_bounds)) {
      mute_toggle *= -1;
    }
    // Unmute and mouse within bounds of volume texture
    else if(mute_toggle == 1 && CheckCollisionPointRec(mouse_position, btn_bounds)) {
      DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
      DrawTexture(game.volume_texture, 385, 550, WHITE);
      SetMusicVolume(game.music, 1);
    }
    // Unmute and mouse NOT within bounds of volume texture
    else if(mute_toggle == 1) {
      DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
      DrawTexture(game.volume_texture, 385, 550, LIGHTGRAY);
      SetMusicVolume(game.music, 1);
    }
    // Mute and mouse within bounds of volume texture
    else if(mute_toggle == -1 && CheckCollisionPointRec(mouse_position, btn_bounds)) {
      DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
      DrawTexture(game.mute_texture, 385, 550, WHITE);
      SetMusicVolume(game.music, 0);
    }
    // Mute and mouse NOT within bounds of volume texture
    else if(mute_toggle == -1) {
      DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
      DrawTexture(game.mute_texture, 385, 550, LIGHTGRAY);
      SetMusicVolume(game.music, 0);
    }

    EndDrawing();
  }

  CloseWindow();
}