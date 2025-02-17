#pragma once
#include <vector>
#include <map>
#include "../header/position.hpp"
#include "../header/colors.hpp"

class Block {
  private:
    int cell_size;
    int rotation_state;
    std::vector<Color> colors;
    int row_offset;
    int column_offset;

  public:
    Block();
    int id;
    std::map<int, std::vector<Position>> cells;
    void draw(int offset_x, int offset_y);
    void move(int rows, int columns);
    std::vector<Position> get_cell_positions();
    void rotate();
    void undo_rotate();
};