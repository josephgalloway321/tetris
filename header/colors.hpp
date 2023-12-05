#pragma once
#include <raylib.h>
#include <vector>

// Cannot use capital constants because definitions from Raylib
extern const Color CUSTOM_DARK_GRAY;
extern const Color CUSTOM_GREEN;
extern const Color CUSTOM_RED;
extern const Color CUSTOM_ORANGE;
extern const Color CUSTOM_YELLOW;
extern const Color CUSTOM_PURPLE;
extern const Color CUSTOM_CYAN;
extern const Color CUSTOM_BLUE;
extern const Color CUSTOM_DARK_BLUE;

std::vector<Color> get_cell_colors();