#pragma once
#include "grid.hpp"
#include "../src/blocks.cpp"

class Game {
  private:
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;
    Grid grid;
    Sound rotate_sound;
    Sound clear_sound;
    bool is_block_outside();
    void rotate_block();
    void lock_block();
    bool block_fits();
    void reset();
    void update_score(int lines_cleared, int move_down_points);
    Block get_random_block();
    std::vector<Block> get_all_blocks();
    void move_block_left();
    void move_block_right();

  public:
    bool game_over;
    int score;
    Music music;
    Game();
    void draw();
    void handle_input();
    void move_block_down();
    ~Game();
};