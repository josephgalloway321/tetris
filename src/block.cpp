#include "../header/block.hpp"
#include "../header/colors.hpp"

Block::Block() {
  cell_size = 30;  // Represents 30 pixels
  rotation_state = 0;
  colors = get_cell_colors();
  row_offset = 0;
  column_offset = 0;
}

void Block::draw(int offset_x, int offset_y) {
  // Get position vector of current rotation state (includes after movement)
  std::vector<Position> tiles = get_cell_positions();
  // Iterate through the positions
  for (Position item : tiles) {
    // Offset each pixel by eleven
    // Shrink to 29 pixels each by subtracting one from cell size width & height
    DrawRectangle(item.column*cell_size + offset_x, item.row*cell_size + offset_y, cell_size - 1, cell_size - 1, colors[id]);  // Use cell_size to focus on coloring only specific cells
  }
}

// Move block origin by a certain number of rows & columns
void Block::move(int rows, int columns) {
  row_offset += rows;
  column_offset += columns;
}

// Calculate position after offset applied then return as vector of positions
// This method is separate from the method above because the 
// calculations above are needed for a different method
std::vector<Position> Block::get_cell_positions() {
  std::vector<Position> tiles = cells[rotation_state];  // Get vector of current position
  std::vector<Position> moved_tiles;  // Empty vector to hold moved tiles
  for (Position item : tiles) {
    Position new_position = Position(item.row + row_offset, item.column + column_offset);
    moved_tiles.push_back(new_position);
  }
  return moved_tiles;
}

void Block::rotate() {
  rotation_state++;
  // Reset rotation state if it exceeds the 4 options
  // cells is a map that contains a vector of all of the rotation states available
  if (rotation_state == (int)cells.size()) {
    rotation_state = 0;
  }
}

void Block::undo_rotate() {
  rotation_state--;
  // Reset rotation state to the second to last option if less than zero
  if (rotation_state == -1) {
    rotation_state = cells.size() - 1;
  }
}