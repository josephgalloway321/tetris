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

  public:
    Grid();
    int grid[20][10];
    void initialize();
    void print() const;
    void draw();
    bool is_cell_outside(int row, int column);
    bool is_cell_empty(int row, int column);
};