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
protected:
    vector<pair<int, int>> tilePositions;

    virtual char getBlockUnit() = 0;
public:
    Block();
    ~Block();
    
    void moveDown();
    void moveLeft();
    void moveRight();
    virtual void rotateCW() = 0;
    virtual void rotateCCW() = 0;
};

#endif