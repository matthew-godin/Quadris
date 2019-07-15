#include "../include/Block.h"

using std::vector;

typedef pair<int, int> int_pair;

// Throws: InvalidBlockType
vector<int_pair> Block::getInitialTilePositionForType(BlockType type) {
    switch (type) {
        case BlockType::I:
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(3, 1),
                int_pair(3, 2),
                int_pair(3, 3)
            };
        case BlockType::J:
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(4, 2)
            };
        case BlockType::L:
            return vector<int_pair>{
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(4, 2),
                int_pair(3, 2)
            };
        case BlockType::O:
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(3, 1)
            };
        case BlockType::S:
            return vector<int_pair>{
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(3, 1),
                int_pair(3, 2)
            };
        case BlockType::Z:
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(3, 1),
                int_pair(4, 1),
                int_pair(4, 2)
            };
        case BlockType::T:
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(3, 1),
                int_pair(3, 2),
                int_pair(4, 1)
            };
            // TODO: throw error if something
        default:
            type = BlockType::EMPTY;
            return vector<int_pair>();
    }
}

Block::Block(BlockType type): 
blockType{type},
hasReachedBottom{false},
tilePositions{Block::getInitialTilePositionForType(type)},
previousTilePositions{Block::getInitialTilePositionForType(type)} {}

Block::~Block() {}

void Block::moveDown() {
    for (auto& tile: tilePositions) {
        tile.first++;
    }
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::moveLeft() {
    for (auto &tile: tilePositions) {
        tile.second--;
    }
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::moveRight() {
    for (auto &tile: tilePositions) {
        tile.second++;
    }
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::rotateCW() {
    // TODO
    // get lower-leftmost unit in block, pivot around that and rotate
    notifyObservers();
}

void Block::rotateCCW() {
    // TODO
    notifyObservers();
}

void Block::didReachBottom() {
    hasReachedBottom = true;
}

vector<int_pair> Block::getTiles() {
    return tilePositions;
}

vector<int_pair> Block::getPreviousTiles() {
    return previousTilePositions;
}

BlockType Block::getBlockType() {
    return blockType;
}