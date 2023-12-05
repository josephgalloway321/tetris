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
bool Grid::is_cell_outside(int row, int column) {
  if (row >= 0 && row < num_rows && column >= 0 && column < num_cols) {
    return false;  // The current block is within the grid boundaries
  }
  return true;
}

// Check if passed in cell is empty or not
bool Grid::is_cell_empty(int row, int column) {
  if(grid[row][column] == 0) {
    return true;
  }
  return false;
}

// Check rows from bottom to top to find full rows
int Grid::clear_full_rows() {
  int completed = 0;
  // Iterate from bottom row to top
  for(int row = num_rows - 1; row >= 0; row--) {
    // Check to see if the row is full
    if(is_row_full(row)) {
      // Since this row is full, clear it
      clear_row(row);
      completed++;  // Keep track of rows completed
    }

    // If the current row is not full but rows have been cleared
    // then move the row down the amount equal to completed
    else if(completed > 0) {
      move_row_down(row, completed);
    }
  }
  return completed;
}

// Check if a row is full starting at the bottom going up
bool Grid::is_row_full(int row) {
  // Iterate across the row
  for(int column = 0; column < num_cols; column++) {
    if(grid[row][column] == 0) {
      return false;
    }
  }
  return true;
}

// Clear the row
void Grid::clear_row(int row) {
  for(int column = 0; column < num_cols; column++) {
    grid[row][column] = 0;
  }
}

// Move the current row down a specific number of rows
void Grid::move_row_down(int row, int num_rows) {
  for(int column = 0; column < num_cols; column++) {
    grid[row + num_rows][column] = grid[row][column];  // Copy values from original row to new (lower) row
    grid[row][column] = 0;  // Erase values in original row
  }
}