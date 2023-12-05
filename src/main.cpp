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

  // TEST
  //LBlock block;
  //JBlock block;
  //IBlock block;
  //OBlock block;
  //SBlock block;
  //TBlock block;
  //ZBlock block;

  // Game loop
  while (WindowShouldClose() == false) {
    // Event handling
    
    // Update

    // Draw
    BeginDrawing();
    ClearBackground(CUSTOM_DARK_BLUE);

    grid.draw();
    //block.draw();  // TEST

    EndDrawing();
  }

  CloseWindow();
}