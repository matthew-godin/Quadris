#include "../include/Board.h"

Board::Board(): 
board{vector<vector<BlockType>>(18, vector<BlockType>(11, BlockType::EMPTY))},
currentBlock{nullptr} {
    // Initialize board with empty blocks

}

Board::~Board() {
    // Deallocate any owned resources
}

void Board::emptyFilledRow(int rowIndex) {
    // Private method that empties out a particular row
}

void Board::reset() {

}

void Board::attemptMoveLeft() {
    // shift current block to the left
}

void Board::attemptMoveRight() {
    // shift current block to the right
}

void Board::attemptMoveDown() {
    // move block down
}

void Board::attemptRotateCW() {
    // Rotate block clockwise
}

void Board::attemptRotateCCW() {
    // Rotate block counter-clockwise
}

void Board::dropToBottom() {
    // take the current block and attempt to move down till
    // it is a valid operation
}

void Board::checkForFilledRow() {
    // parse throw board
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