#include "../include/Block.h"

using std::vector;

typedef pair<int, int> int_pair;

// Throws: InvalidBlockType
vector<int_pair> Block::getInitialTilePositionForType(BlockType type) {
    switch (type) {
        case BlockType::I:
            return vector<int_pair>{
                int_pair(0, 0),
                int_pair(0, 1),
                int_pair(0, 2),
                int_pair(0, 3)
            };
        case BlockType::J:
            return vector<int_pair>{
                int_pair(0, 0),
                int_pair(1, 0),
                int_pair(1, 1),
                int_pair(1, 2)
            };
        case BlockType::L:
            return vector<int_pair>{
                int_pair(1, 0),
                int_pair(1, 1),
                int_pair(1, 2),
                int_pair(0, 2)
            };
        case BlockType::O:
            return vector<int_pair>{
                int_pair(0, 0),
                int_pair(1, 0),
                int_pair(1, 1),
                int_pair(0, 1)
            };
        case BlockType::S:
            return vector<int_pair>{
                int_pair(1, 0),
                int_pair(1, 1),
                int_pair(0, 1),
                int_pair(0, 2)
            };
        case BlockType::Z:
            return vector<int_pair>{
                int_pair(0, 0),
                int_pair(0, 1),
                int_pair(1, 1),
                int_pair(1, 2)
            };
        case BlockType::T:
            return vector<int_pair>{
                int_pair(0, 0),
                int_pair(0, 1),
                int_pair(0, 2),
                int_pair(1, 1)
            };
        case BlockType::EMPTY:
            return vector<int_pair>();
    }
}

Block::Block(BlockType type): 
blockType{type},
tilePositions{Block::getInitialTilePositionForType(type)} {}

Block::~Block() {}

void Block::moveDown() {

}

void Block::moveLeft() {

}

void Block::moveRight() {

}

void Block::rotateCW() {

}

void Block::rotateCCW() {

}