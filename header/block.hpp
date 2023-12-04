#pragma once
#include <vector>
#include <map>
#include "../header/position.hpp"
#include "../header/colors.hpp"

class Block {
  private:
    int cell_size;
    int rotation_state;

  public:
    Block();
    int id;
    std::map<int, std::vector<Position>> cells;
};