#include "../header/game.hpp"
#include <random>

Game::Game() {
  game_over = false;
  score = 0;
  high_score = 0;
  blocks = get_all_blocks();  // Vector holds available block options
  current_block = get_random_block();
  next_block = get_random_block();
  is_paused = false;

  // Font and textures
  font = LoadFontEx("C:/Users/josep/Documents/GitHub/tetris/resources/font/monogram.ttf", 64, 0, 0);
  volume_image = LoadImage("C:/Users/josep/Documents/GitHub/tetris/resources/images/volume.png");
  mute_image = LoadImage("C:/Users/josep/Documents/GitHub/tetris/resources/images/mute.png");
  volume_texture = LoadTextureFromImage(volume_image);
  mute_texture = LoadTextureFromImage(mute_image);
  UnloadImage(volume_image); // Image converted to texture & uploaded to VRAM, it can be unloaded now
  UnloadImage(mute_image);
  sound_btn_bounds = {385, 550, 50, 40};

  // Game aduio
  InitAudioDevice();
  music = LoadMusicStream("C:/Users/josep/Documents/GitHub/tetris/resources/sounds/music.mp3");
  rotate_sound = LoadSound("C:/Users/josep/Documents/GitHub/tetris/resources/sounds/rotate.mp3");
  clear_sound = LoadSound("C:/Users/josep/Documents/GitHub/tetris/resources/sounds/clear.mp3");
  is_mute = false;
}

Game::~Game() {
  UnloadFont(font);
  UnloadTexture(volume_texture);
  UnloadTexture(mute_texture);
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
    default:
      break;
  }

  // Check if down key held down
  // TODO: Blocks fall down WAY too fast
  /*
  if(IsKeyDown(KEY_DOWN)) {
    move_block_down();
    update_score(0, 1);
  }
  */
}

// Highlight volume button when mouse hovers
// Toggle volume on/off when clicked
// Button clicked within bounds, toggle
void Game::handle_sound_toggle() {
  mouse_position = GetMousePosition();

  // Check if user within sound button bounds and clicked
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_position, sound_btn_bounds)) {
      is_mute = !is_mute;
  }
  
  // Unmute and mouse within bounds of volume texture
  if(is_mute == false && CheckCollisionPointRec(mouse_position, sound_btn_bounds)) {
    DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
    DrawTexture(volume_texture, 385, 550, WHITE);
    SetMusicVolume(music, 1);
    SetSoundVolume(rotate_sound, 1);
    SetSoundVolume(clear_sound, 1);
  }
  // Unmute and mouse NOT within bounds of volume texture
  else if(is_mute == false) {
    DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
    DrawTexture(volume_texture, 385, 550, LIGHTGRAY);
    SetMusicVolume(music, 1);
    SetSoundVolume(rotate_sound, 1);
    SetSoundVolume(clear_sound, 1);
  }
  // Mute and mouse within bounds of volume texture
  else if(is_mute == true && CheckCollisionPointRec(mouse_position, sound_btn_bounds)) {
    DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
    DrawTexture(mute_texture, 385, 550, WHITE);
    SetMusicVolume(music, 0);
    SetSoundVolume(rotate_sound, 0);
    SetSoundVolume(clear_sound, 0);
  }
  // Mute and mouse NOT within bounds of volume texture
  else if(is_mute == true) {
    DrawRectangle(385, 550, 50, 50, CUSTOM_DARK_BLUE);
    DrawTexture(mute_texture, 385, 550, LIGHTGRAY);
    SetMusicVolume(music, 0);
    SetSoundVolume(rotate_sound, 0);
    SetSoundVolume(clear_sound, 0);
  }
}

// Pause/Resume the game
void Game::pause_game() {
  is_paused = !is_paused;
}

bool Game::get_is_paused() {
  return is_paused;
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
  game_over = false;
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