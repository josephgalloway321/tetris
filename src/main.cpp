#include <iostream>
#include <raylib.h>
#include "../header/grid.hpp"
#include "../header/colors.hpp"
#include "blocks.cpp"

int main()
{
  // Game Definitions & Initializations
  InitWindow(300, 600, "Tetris");
  SetTargetFPS(60);

  // Create game objects
  Grid grid;
  //grid.print();
  LBlock l_block;
  JBlock j_block;
  IBlock i_block;
  OBlock o_block;
  SBlock s_block;
  TBlock t_block;
  ZBlock z_block;

  // Game loop
  while (WindowShouldClose() == false) {
    // Event handling
    
    // Update

    // Draw
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);

    grid.draw();
    z_block.draw();

    EndDrawing();
  }

  CloseWindow();
}