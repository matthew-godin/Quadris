#include "../include/Board.h"
#include <vector>
#include <algorithm>

using std::vector;
typedef pair<int, int> int_pair;

// Default Methods

Board::Board(): 
board{vector<vector<BlockType>>(Board::MAX_BOARD_ROWS, vector<BlockType>(Board::MAX_BOARD_COLUMNS, BlockType::EMPTY))},
currentBlock{nullptr} {
    // Initialize board with empty blocks

}

Board::~Board() {
    // Deallocate any owned resources
}

// Private Methods

void Board::emptyFilledRow(int rowToEmpty) {
    // Private method that empties out a particular row
    for (auto &c: board.at(rowToEmpty)) {
        c = BlockType::EMPTY;
    }
}

void Board::moveBlocksDown(int lastEmptyRow) {
    // avoid moving these coordinates down
    auto currentBlockCoordinates = currentBlock->getTiles();
    if (lastEmptyRow < 4 || lastEmptyRow >= Board::MAX_BOARD_ROWS) return;

    int numRowsToMoveDown = board.size() - lastEmptyRow;
    std::cout << "Moving row " << lastEmptyRow - 1 << " down by " << numRowsToMoveDown << (numRowsToMoveDown == 1 ? " row" : " rows") << std::endl;
    for (int i = lastEmptyRow - 1; i >= 3; --i) {
        bool isAnEntireLineEmpty = true;
        for (int j = 0; j < Board::MAX_BOARD_COLUMNS; ++j) {
            if (board.at(i).at(j) == BlockType::EMPTY) continue;

            isAnEntireLineEmpty = false;
            // Check if the part of board we're moving down belongs to current block
            pair<int, int> modifiedBlockCoordinates = pair<int, int>(i, j);
            auto it = find(currentBlockCoordinates.begin(), currentBlockCoordinates.end(), modifiedBlockCoordinates);
            
            // Don't move block down if it is the one being controlled by the user
            if (it != currentBlockCoordinates.end()) continue;
            // otherwise move it down
            board.at(i + numRowsToMoveDown).at(j) = board.at(i).at(j);
            board.at(i).at(j) = BlockType::EMPTY;
        }

        if (isAnEntireLineEmpty) break;
    }
}

// Requires: rowIndex & columnIndex are within bounds of the board
bool Board::isBoardEmptyAt(std::pair<int, int> coordinate) {
    int rowIndex = coordinate.first;
    int columnIndex = coordinate.second;
    return board.at(rowIndex).at(columnIndex) == BlockType::EMPTY;
}

void Board::checkForFilledRow() {
    int lastEmptyRow = board.size();
    // parse throw board
    for (int back = board.size() - 1; back > 3; --back) {
        bool isFull = true;
        for (auto column: board.at(back)) {
            isFull = isFull && (column != BlockType::EMPTY);
            if (!isFull) break;
        }
        if (isFull) {
            std::cout << "Row " << back << " is full." << std::endl;
            emptyFilledRow(back);
            lastEmptyRow = back;
            moveBlocksDown(lastEmptyRow);
        }
    }
}

// Overridden Observer Methods

void Board::notify(Subject* subject) {
    // Consider this to be a block. Update your board accordingly
    shared_ptr<Block> modifiedBlock = nullptr;
    for (auto &block: blocks) {
        if (subject == block.get()) {
            modifiedBlock = block;
        }
    }
    
    if (modifiedBlock != nullptr) {
        // Update view with modified block
        auto oldTiles = modifiedBlock->getPreviousTiles();
        auto newTiles = modifiedBlock->getTiles();

        for  (int i = 0; i < oldTiles.size(); i++) {
            board.at(oldTiles.at(i).first).at(oldTiles.at(i).second) = BlockType::EMPTY;
        }

        for  (int i = 0; i < newTiles.size(); i++) {
            board.at(newTiles.at(i).first).at(newTiles.at(i).second) = modifiedBlock->getBlockType();
        }
        
    }

    return;
}

// Public interface methods

void Board::reset() {
    // Empty the board

    // Empty the blocks vector

    // Empty the blocks queue

    // Remove the reference to the current block
}

bool Board::attemptInsertBlockIntoBoard(shared_ptr<Block> b) {
    // vector as current block
    currentBlock = b;
    // Add this as observer
    b->attach(this);
    // Add block to blocks
    blocks.emplace_back(b);
    // Add to blocks queue
    if (queuedBlocks.size() == Board::MAX_QUEUE_SIZE) {
        // Empty queue, maybe clear the last line
    }
    queuedBlocks.push(b);
    // Add block to board
    for (auto &coordinate: b->getTiles()) {
        if (board.at(coordinate.first).at(coordinate.second) != BlockType::EMPTY) return false;
        board.at(coordinate.first).at(coordinate.second) = b->getBlockType();
    }
    return true;
}

bool Board::attemptMoveLeft() {
    if (currentBlock == nullptr) return false;
    auto positions = currentBlock->getTiles();
    // Calculate bounds within which the board can move
    for (auto &coordinate: positions) {
        // already at the left-most position within board
        if (coordinate.second == 0) {
            return false;
        }
        
        auto futureCoordinate = coordinate;
        futureCoordinate.second--;
        bool isNotSameBlock = find(positions.begin(), positions.end(), futureCoordinate) == positions.end();
        if (isNotSameBlock && !isBoardEmptyAt(futureCoordinate)) {
            return false;
        }
    }

    currentBlock->moveLeft();
    std::cout << *this << std::endl;
    return true;
}

bool Board::attemptMoveRight() {
    vector<int_pair> positions = currentBlock->getTiles();
    
    for (int_pair & coordinate : positions) {
        if (coordinate.second == Board::MAX_BOARD_COLUMNS - 1) {
            return false;
        }
        
        int_pair futureCoordinate = coordinate;
        futureCoordinate.second++;

        bool isNotSameBlock = find(positions.begin(), positions.end(), futureCoordinate) == positions.end();
        if (isNotSameBlock && !isBoardEmptyAt(futureCoordinate)) {
            return false;
        }
    }
    currentBlock->moveRight();
    return true;
}

bool Board::canMoveDownAgain() {
    vector<int_pair> positions = currentBlock->getTiles();

    for (int_pair & coordinate: positions) {
        if (coordinate.first == Board::MAX_BOARD_ROWS - 1) {
            return false;
        }
        auto futureCoordinate(coordinate);
        futureCoordinate.first++;
        bool isNotSameBlock = find(positions.begin(), positions.end(), futureCoordinate) == positions.end();
        if (isNotSameBlock && !isBoardEmptyAt(futureCoordinate)) {
            return false;
        }
    }
    return true;
}

bool Board::moveDown() {
    if (!canMoveDownAgain()) {
        return false;
    }
    currentBlock->moveDown();
    return true;
} 

bool Board::attemptRotateCW() {
    // Rotate block clockwise
    vector<int_pair> positions = currentBlock->getTiles();
    int temp;
    for (int_pair & coordinate : positions) {
        auto futureCoordinate(coordinate);
        temp = futureCoordinate.first;
        futureCoordinate.first = currentBlock->getMaxY() - (currentBlock->getMaxX() - futureCoordinate.second);
        futureCoordinate.second = currentBlock->getMinX() + (currentBlock->getMaxY() - temp);
        if (futureCoordinate.first >= Board::MAX_BOARD_ROWS || futureCoordinate.second < 0 || futureCoordinate.second >= Board::MAX_BOARD_COLUMNS) {
            return false;
        }
        bool isNotSameBlock = find(positions.begin(), positions.end(), futureCoordinate) == positions.end();
        if (isNotSameBlock && !isBoardEmptyAt(futureCoordinate)) {
            return false;
        }
    }
    currentBlock->rotateCW();
    return true;
}

bool Board::attemptRotateCCW() {
    // Rotate block counter-clockwise
    vector<int_pair> positions = currentBlock->getTiles();
    int temp;
    for (int_pair & coordinate : positions) {
        auto futureCoordinate(coordinate);
        temp = futureCoordinate.first;
        futureCoordinate.first = currentBlock->getMaxY() - (currentBlock->getMaxX() - futureCoordinate.second);
        futureCoordinate.second = currentBlock->getMinX() + (currentBlock->getMaxY() - temp);
        if (futureCoordinate.first >= Board::MAX_BOARD_ROWS || futureCoordinate.second < 0 || futureCoordinate.second >= Board::MAX_BOARD_COLUMNS) {
            return false;
        }
        bool isNotSameBlock = find(positions.begin(), positions.end(), futureCoordinate) == positions.end();
        if (isNotSameBlock && !isBoardEmptyAt(futureCoordinate)) {
            return false;
        }
    }
    currentBlock->rotateCCW();
    return true;
}

bool Board::dropToBottom() {
    // take the current block and attempt to move down till
    // it is a valid operation

    while (true) {
        bool wasMoveDownSuccessful = moveDown();
        if (!wasMoveDownSuccessful) break;
    }
    return true;
}

ostream& operator<<(ostream& out, const Board& b) {
    for (auto &rows: b.board) {
        out << "|";
        for (auto &column: rows) {
            out << " " << static_cast<char>(column) << " |";
        }
        out << std::endl;
    }

    return out;
}

BlockType Board::getTypeAt(int i, int j) {
    return board[i][j];
}

int Board::getBoardLength() {
    return board[0].size();
}

int Board::getBoardHeight() {
    return board.size();
}
