#ifndef BLOCK_H_
#define BLOCK_H_

#include "Subject.h"

class Block: public Subject {
protected:
    std::vector<std::pair<int, int>> tiles;
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