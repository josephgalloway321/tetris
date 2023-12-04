#pragma once
#include <vector>
#include <raylib.h>

class Grid {
  private:
    int num_rows;
    int num_cols;
    int cell_size;  // Size of each grid cell in pixels
    std::vector<Color> colors;
    std::vector<Color> get_cell_colors() const;

  public:
    Grid();
    int grid[20][10];
    void initialize();
    void print() const;
    void draw();
};