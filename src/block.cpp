#include "../header/block.hpp"
#include "../header/colors.hpp"

Block::Block() {
  cell_size = 30;  // Represents 30 pixels
  rotation_state = 0;
  colors = get_cell_colors();
}

void Block::draw() {
  std::vector<Position> tiles = cells[rotation_state];  // Get position vector of current rotation state
  // Iterate through the positions
  for (Position item : tiles) {
    // Offset each pixel by one
    // Shrink to 29 pixels each by subtracting one from cell size width & height
    DrawRectangle(item.column*cell_size+1, item.row*cell_size+1, cell_size-1, cell_size-1, colors[id]);  // Use cell_size to focus on coloring only specific cells
  }
}