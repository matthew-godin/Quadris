#ifndef BOARD_H_
#define BOARD_H_

#include "Block.h"
#include <queue>
#include <iostream>

using std::vector;
using std::shared_ptr;
using std::queue;
using std::ostream;

class Board {
    vector<vector<BlockType>> board;
    vector<shared_ptr<Block>> blocks;
    bool isGettingRandomBlocks;
    queue<shared_ptr<Block>> queuedBlocks;
    shared_ptr<Block> currentBlock;

    void emptyFilledRow(int);
public:
    Board();
    virtual ~Board();

    // Resets the boards contents
    void reset();

    void attemptMoveLeft();
    void attemptMoveRight();
    void attemptMoveDown();
    void attemptRotateCW();
    void attemptRotateCCW();
    void dropToBottom();
    void checkForFilledRow();

    friend ostream& operator<<(ostream&, const Board& b);
};

#endif