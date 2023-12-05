#include <iostream>
#include "../header/grid.hpp"

// Default constructor
Grid::Grid() {
  num_rows = 20;
  num_cols = 10;
  cell_size = 30;
  initialize();
  colors = get_cell_colors();
}

// Initialize the grid to all zeros so everything is empty
void Grid::initialize() {
  for (int row = 0; row < num_rows; row++) {
    for (int column = 0; column < num_cols; column++) {
      grid[row][column] = 0;
    }
  }
}

// Print the value of each grid value in the terminal
// Used primarily for testing & debugging
void Grid::print() const {
  for (int row = 0; row < num_rows; row++) {
    for (int column = 0; column < num_cols; column++) {
      std::cout << grid[row][column] << " ";
    }
    std::cout << "\n";
  }
}

// Draw the appropriate color for specific cells
// Iterate through each cell in the grid, find the cell values, and then assign a color
void Grid::draw() {
  for (int row = 0; row < num_rows; row++) {
    for (int column = 0; column < num_cols; column++) {
      int cell_value = grid[row][column];
      // Offset each pixel by one
      // Shrink to 29 pixels each by subtracting one from cell size width & height
      DrawRectangle(column*cell_size+1, row*cell_size+1, cell_size-1, cell_size-1, colors[cell_value]);  // Use cell_size to focus on coloring only specific cells
    }
  }
}

// Check if a cell from the current block is outside any of the grid boundaries
bool Grid::is_cell_outside (int row, int column) {
  if (row >= 0 && row < num_rows && column >= 0 && column < num_cols) {
    return false;  // The current block is within the grid boundaries
  }
  return true;
}