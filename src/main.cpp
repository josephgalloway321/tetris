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
  enum GameScreen {title, gameplay, ending};
  GameScreen current_screen = title;  // Start the game on the title screen

  // Create game objects
  Game game;
  Timer block_fall_speed_timer;
  
  // Game loop
  while (WindowShouldClose() == false) {
    /***********************************
    * Update
    ***********************************/
    switch(current_screen) {
      case title: {
        if(IsKeyPressed(KEY_SPACE)) {
          // Proceed to gameplay screen
          current_screen = gameplay;
          PlayMusicStream(game.music);
        }
      } break;
      
      case gameplay: {
        // Handle user input
        game.handle_input();
        game.handle_sound_toggle();

        // Handle time passed to regulate block falling speed
        if(block_fall_speed_timer.elapsed() > BLOCK_FALL_SPEED) {
          game.move_block_down();
          block_fall_speed_timer.reset_timer();
        }

        // Update background music
        UpdateMusicStream(game.music);

        // Check if game over
        if(game.is_game_over()) {
          current_screen = ending;
          StopMusicStream(game.music);
        }
      } break;

      case ending: {
        game.reset();
        if(IsKeyPressed(KEY_SPACE)) {
          // Proceed to title screen
          current_screen = title;
        }
      } break;
      
      default:
        break;
    }



    /***********************************
    *  Draw
    ***********************************/
    BeginDrawing();

    switch(current_screen) {
      case title: {
        ClearBackground(CUSTOM_DARK_BLUE);
        DrawTextEx(game.font, "Tetris", {100, 100}, 42, 2, BLACK);
      } break;

      case gameplay: {
        ClearBackground(CUSTOM_DARK_BLUE);

        // User interface
        DrawTextEx(game.font, "High Score", {325, 20}, 32, 2, WHITE);
        DrawRectangleRounded({320, 70, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
        DrawTextEx(game.font, "Score", {360, 150}, 32, 2, WHITE);
        DrawRectangleRounded({320, 200, 170, 60}, 0.3, 6, CUSTOM_LIGHT_BLUE);
        DrawTextEx(game.font, "Next", {370, 280}, 32, 2, WHITE);
        DrawRectangleRounded({320, 330, 170, 180}, 0.3, 6, CUSTOM_LIGHT_BLUE);

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

      } break;

      case ending: {
        ClearBackground(BLACK);
        DrawTextEx(game.font, "Game Over", {100, 100}, 42, 2, RED);
        
      } break;

      default: 
        break;
    }

    EndDrawing();
  }

  CloseWindow();
}