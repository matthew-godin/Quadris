#ifndef BOARD_H_
#define BOARD_H_

#include "Block.h"
#include <queue>
#include <iostream>

using std::vector;
using std::shared_ptr;
using std::pair;
using std::queue;
using std::ostream;

class Board: public Observer {
    static const size_t MAX_QUEUE_SIZE = 0;
    static const size_t MAX_BOARD_ROWS = 18;
    static const size_t MAX_BOARD_COLUMNS = 11;

    vector<vector<BlockType>> board;
    vector<shared_ptr<Block>> blocks;
    queue<shared_ptr<Block>> queuedBlocks;
    shared_ptr<Block> currentBlock;

    void emptyFilledRow(int);
    bool isBoardEmptyAt(pair<int, int>);
    bool canMoveDownAgain();
public:
    Board();
    
    virtual ~Board();

    virtual void notify(Subject*) override;
    // Resets the boards contents
    void reset();

    bool attemptInsertBlockIntoBoard(shared_ptr<Block>);

    // Returns: returns true if successful, returns false if unsuccessful
    bool attemptMoveLeft();
    // Returns: returns true if successful, returns false if unsuccessful
    bool attemptMoveRight();
    // Returns: returns true if successful, returns false if unsuccessful
    bool moveDown();
    // Returns: returns true if successful, returns false if unsuccessful
    bool attemptRotateCW();
    // Returns: returns true if successful, returns false if unsuccessful
    bool attemptRotateCCW();
    bool dropToBottom();
    void checkForFilledRow();

    friend ostream& operator<<(ostream&, const Board& b);

    BlockType getTypeAt(int i, int j);
    int getBoardLength();
    int getBoardHeight();
};

#endif
