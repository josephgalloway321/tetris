#include "../header/game.hpp"
#include <random>

Game::Game() {
  game_over = false;
  blocks = get_all_blocks();  // Vector holds available block options
  current_block = get_random_block();
  next_block = get_random_block();
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
  current_block.draw();
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
  }

  next_block = get_random_block();
  grid.clear_full_rows();
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
}