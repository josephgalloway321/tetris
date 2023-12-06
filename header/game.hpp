#pragma once
#include "grid.hpp"
#include "../src/blocks.cpp"

class Game {
  private:
    int score;
    int high_score;
    bool game_over;
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
    void update_high_score();

  public:
    Music music;
    Font font;
    Image volume_image;
    Texture2D volume_texture;
    Game();
    int get_score();
    int get_high_score();
    bool is_game_over();
    void draw();
    void handle_input();
    void move_block_down();
    ~Game();
};