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

// Get color options for each grid cell
std::vector<Color> Grid::get_cell_colors() const {
  const Color dark_grey = {26, 31, 40, 255};
  const Color green = {47, 230, 23, 255};
  const Color red = {232, 18, 18, 255};
  const Color orange = {226, 116, 17, 255};
  const Color yellow = {237, 234, 4, 255};
  const Color purple = {166, 0, 247, 255};
  const Color cyan = {21, 204, 209, 255};
  const Color blue = {13, 64, 216, 255};

  return {dark_grey, green, red, orange, yellow, purple, cyan, blue};
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