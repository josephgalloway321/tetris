#include "../header/game.hpp"
#include <random>

Game::Game() {
  game_over = false;
  score = 0;
  high_score = 0;
  blocks = get_all_blocks();  // Vector holds available block options
  current_block = get_random_block();
  next_block = get_random_block();

  // Game images
  

  // Game aduio
  InitAudioDevice();
  music = LoadMusicStream("C:/Users/josep/Documents/GitHub/tetris/resources/sounds/music.mp3");
  rotate_sound = LoadSound("C:/Users/josep/Documents/GitHub/tetris/resources/sounds/rotate.mp3");
  clear_sound = LoadSound("C:/Users/josep/Documents/GitHub/tetris/resources/sounds/clear.mp3");
  PlayMusicStream(music);
}

Game::~Game() {
  // Game images
  //UnloadTexture(volume);

  // Game audio
  UnloadSound(rotate_sound);
  UnloadSound(clear_sound);
  UnloadMusicStream(music);
  CloseAudioDevice();
}

// Return a random block from the vector that holds all block options
Block Game::get_random_block() {
  // Make sure the vector containing the blocks options is full
  if (blocks.empty()) {
    blocks = get_all_blocks();
  }

  // Make sure each block appears at least once before calling a block again
  int random_index = rand() % blocks.size();  // Numbers 0 to 6
  Block block = blocks[random_index];  // Store block chosen
  blocks.erase(blocks.begin() + random_index);  // Erase block chosen from blocks vector
  return block;
}

std::vector<Block> Game::get_all_blocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::draw() {
  grid.draw();
  current_block.draw(11, 11);

  // Slightly adjust I and O blocks to center on "Next Block" part of interface
  switch(next_block.id) {
    // I block
    case 3:
      next_block.draw(255, 400);
      break;
    // O block
    case 4:
      next_block.draw(255, 380);
      break;
    default:
      next_block.draw(270, 390);
      break;
  }
}

void Game::handle_input() {
  int key_pressed = GetKeyPressed();

  // If no key is pressed, then key_pressed is 0
  if(game_over && key_pressed != 0) {
    game_over = false;
    reset();
  }

  switch(key_pressed) {
    case KEY_LEFT:
      move_block_left();
      break;
    case KEY_RIGHT:
      move_block_right();
      break;
    case KEY_DOWN:
      move_block_down();
      update_score(0, 1);
      break;
    case KEY_UP:
      rotate_block();
      break;
  }
}

// Increase current block offset so draw will update accordingly
void Game::move_block_left() {
  if(!game_over) {
    current_block.move(0, -1);
    if (is_block_outside() || block_fits() == false) {
      current_block.move(0, 1);  // Move back within bounds
    }
  }
}

// Increase current block offset so draw will update accordingly
void Game::move_block_right() {
  if(!game_over) {
    current_block.move(0, 1);
    if (is_block_outside() || block_fits() == false) {
      current_block.move(0, -1);  // Move back within bounds
    }
  } 
}

// Increase current block offset so draw will update accordingly
void Game::move_block_down() {
  if(!game_over) {
    current_block.move(1, 0);
    if (is_block_outside() || block_fits() == false) {
      current_block.move(-1, 0);  // Move back within bounds
      lock_block();
    }
  } 
}

// Check if any tile in the current block is outside of the grid
bool Game::is_block_outside() {
  std::vector<Position> tiles = current_block.get_cell_positions();
  for (Position item : tiles) {
    if (grid.is_cell_outside(item.row, item.column)) {
      return true;
    }
  }
  return false;
}

void Game::rotate_block() {
  current_block.rotate();
  if (is_block_outside() || block_fits() == false) {
    current_block.undo_rotate();
  }
  else {
    PlaySound(rotate_sound);
  }
}

// Update grid values to represent locked block when touches bottom screen
void Game::lock_block() {
  // Get the vector of positions for current block in grid
  std::vector<Position> tiles = current_block.get_cell_positions();
  for (Position item : tiles) {
    grid.grid[item.row][item.column] = current_block.id;
  }
  current_block = next_block;

  // If the current block does not fit during spawn, then game over
  if(block_fits() == false) {
    game_over = true;
    update_high_score();
  }

  next_block = get_random_block();
  int rows_cleared = grid.clear_full_rows();
  if(rows_cleared > 0) {
    PlaySound(clear_sound);
    update_score(rows_cleared, 0);
  }
}

// Check if any of the cells in the 3x3 cell grid are occupied
bool Game::block_fits() {
  // First, get the positions of each cell for the current block
  std::vector<Position> tiles = current_block.get_cell_positions();
  for(Position item : tiles) {
    if(grid.is_cell_empty(item.row, item.column) == false) {
      return false;
    }
  }
  return true;
}

void Game::reset() {
  grid.initialize();
  blocks = get_all_blocks();
  current_block = get_random_block();
  next_block = get_random_block();
  score = 0;
}

void Game::update_score(int lines_cleared, int move_down_points) {
  switch(lines_cleared) {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 500;
      break;
    default:
      break;
  }
  score += move_down_points;
}

bool Game::is_game_over() {
  return game_over;
}

int Game::get_score() {
  return score;
}

int Game::get_high_score() {
  return high_score;
}

void Game::update_high_score() {
  if(score > high_score) {
    high_score = score;
  }
}