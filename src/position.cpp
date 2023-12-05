#include "../header/position.hpp"

// Default constructor
// Used to represent a single position on the grid with a single object
Position::Position(int row, int column) {
  // The this keyword assigns the row & column parameters to the row & column attributes
  this -> row = row;
  this -> column = column;
}