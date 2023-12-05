#include <vector>
#include "../header/colors.hpp"

const Color CUSTOM_DARK_GRAY = {26, 31, 40, 255};
const Color CUSTOM_GREEN = {47, 230, 23, 255};
const Color CUSTOM_RED = {232, 18, 18, 255};
const Color CUSTOM_ORANGE = {226, 116, 17, 255};
const Color CUSTOM_YELLOW = {237, 234, 4, 255};
const Color CUSTOM_PURPLE = {166, 0, 247, 255};
const Color CUSTOM_CYAN = {21, 204, 209, 255};
const Color CUSTOM_BLUE = {13, 64, 216, 255};
const Color CUSTOM_DARK_BLUE = {44, 44, 127, 255};
const Color CUSTOM_LIGHT_BLUE = {59, 85, 162, 255};

std::vector<Color> get_cell_colors() {
  return {CUSTOM_DARK_GRAY, CUSTOM_GREEN, CUSTOM_RED, CUSTOM_ORANGE, 
  CUSTOM_YELLOW, CUSTOM_PURPLE, CUSTOM_CYAN, CUSTOM_BLUE};
}