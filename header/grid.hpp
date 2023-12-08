#pragma once
#include <vector>
#include <raylib.h>
#include "../header/colors.hpp"

class Grid {
  private:
    int num_rows;
    int num_cols;
    int cell_size;  // Size of each grid cell in pixels
    std::vector<Color> colors;
    bool is_row_full(int row);
    void clear_row(int row);
    void move_row_down(int row, int num_rows);

  public:
    Grid();
    int grid[20][10];
    void initialize();
    void draw();
    bool is_cell_outside(int row, int column);
    bool is_cell_empty(int row, int column);
    int clear_full_rows();
};