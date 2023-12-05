#pragma once
#include <vector>
#include "grid.hpp"
#include "../src/blocks.cpp"

class Game {
  private:
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;
    bool is_block_outside();
    void rotate_block();
    void lock_block();
    bool block_fits();
    void reset();

  public:
    Grid grid;
    bool game_over;
    Game();
    Block get_random_block();
    std::vector<Block> get_all_blocks();
    void draw();
    void handle_input();
    void move_block_left();
    void move_block_right();
    void move_block_down();
};