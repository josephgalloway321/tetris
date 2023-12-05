// Create the child classes for each block type
#include "../header/block.hpp"
#include "../header/position.hpp"

class LBlock : public Block {
  public:
    LBlock() {
      id = 1;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)};
      cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
      cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
      cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
    }
};

class JBlock : public Block {
  public:
    JBlock() {
      id = 2;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
      cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
      cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
      cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
    }
};

class IBlock : public Block {
  public:
    IBlock() {
      id = 3;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
      cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
      cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
      cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
    }
};

class OBlock : public Block {
  public:
    OBlock() {
      id = 4;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
      cells[1] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
      cells[2] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
      cells[3] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
    }
};

class SBlock : public Block {
  public:
    SBlock() {
      id = 5;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
      cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
      cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
      cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
    }
};

class TBlock : public Block {
  public:
    TBlock() {
      id = 6;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
      cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
      cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
      cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
    }
};

class ZBlock : public Block {
  public:
    ZBlock() {
      id = 7;
      // Rotation state x, vector holds positions occupied at this rotation state
      cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
      cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
      cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
      cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
    }
};