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
    int blockLevel;
    bool isHeavy;
    bool hasReachedBottom;
    
    // Order of tile positions doesn't matter
    vector<pair<int, int>> tilePositions;
    int minX, minY, maxX, maxY;
    // Previous tile positions
    vector<pair<int, int>> previousTilePositions;

    
    static vector<pair<int,int>> getInitialTilePositionForType(BlockType, int&, int&, int&, int&);
public:
    Block(BlockType, int);
    
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
    int getLevel();
    bool isAHeavyBlock();

    int getMinX();
    int getMinY();
    int getMaxX();
    int getMaxY();
};

#endif
