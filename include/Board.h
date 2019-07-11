#ifndef BOARD_H_
#define BOARD_H_

#include "Block.h"

using std::vector;
using std::shared_ptr;
using std::queue;

class Board {
    vector<vector<BlockType>> board;
    vector<Block> blocks;
    bool isGettingRandomBlocks;
    queue<Block> queuedBlocks;
    shared_ptr<Block> currentBlock;

    void emptyFilledRow(int);
public:
    Board();
    virtual ~Board();

    void attemptMoveLeft();
    void attemptMoveRight();
    void attemptRotateCW();
    void attemptRotateCCW();
    void dropToBottom();
    void checkForFilledRow();
};

#endif