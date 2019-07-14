#ifndef BLOCK_H_
#define BLOCK_H_

#include "Subject.h"

using std::vector;
using std::pair;

enum BlockType {
    I = 'I',
    J = 'J',
    L = 'L',
    O = 'O',
    S = 'S',
    Z = 'Z',
    T = 'T',
    EMPTY = ' '
};

class Block: public Subject {
    BlockType blockType;
    // Order of tile positions doesn't matter
    vector<pair<int, int>> tilePositions;

    static vector<pair<int,int>> getInitialTilePositionForType(BlockType);
    char getBlockUnit();
public:
    Block(BlockType);
    ~Block();
    
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotateCW();
    void rotateCCW();
};

#endif