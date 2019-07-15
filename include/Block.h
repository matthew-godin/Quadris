#ifndef BLOCK_H_
#define BLOCK_H_

#include "Subject.h"

using std::vector;
using std::pair;

enum BlockType: char {
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
    bool hasReachedBottom;
    
    // Order of tile positions doesn't matter
    vector<pair<int, int>> tilePositions;
    // Previous tile positions
    vector<pair<int, int>> previousTilePositions;

    
    static vector<pair<int,int>> getInitialTilePositionForType(BlockType);
public:
    Block(BlockType type);
    
    ~Block();
    
    void moveDown();
    void moveLeft();
    void moveRight();
    void rotateCW();
    void rotateCCW();

    void didReachBottom();

    vector<pair<int, int>> getTiles();
    vector<pair<int, int>> getPreviousTiles();
    BlockType getBlockType();
};

#endif