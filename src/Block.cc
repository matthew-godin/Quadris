#include "../include/Block.h"
#include <iostream>

using std::vector;

typedef pair<int, int> int_pair;

// Throws: InvalidBlockType
vector<int_pair> Block::getInitialTilePositionForType(BlockType type, int &minX, int &minY, int &maxX, int &maxY) {
    switch (type) {
        case BlockType::I:
            minX = 0;
            minY = maxY = 3;
            maxX = 3;
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(3, 1),
                int_pair(3, 2),
                int_pair(3, 3)
            };
        case BlockType::J:
            minX = 0;
            minY = 3;
            maxX = 2;
            maxY = 4;
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(4, 2)
            };
        case BlockType::L:
            minX = 0;
            minY = 3;
            maxX = 2;
            maxY = 4;
            return vector<int_pair>{
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(4, 2),
                int_pair(3, 2)
            };
        case BlockType::O:
            minX = 0;
            minY = 3;
            maxX = 1;
            maxY = 4;
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(3, 1)
            };
        case BlockType::S:
            minX = 0;
            minY = 3;
            maxX = 2;
            maxY = 4;
            return vector<int_pair>{
                int_pair(4, 0),
                int_pair(4, 1),
                int_pair(3, 1),
                int_pair(3, 2)
            };
        case BlockType::Z:
            minX = 0;
            minY = 3;
            maxX = 2;
            maxY = 4;
            return vector<int_pair>{
                int_pair(3, 0),
                int_pair(3, 1),
                int_pair(4, 1),
                int_pair(4, 2)
            };
        case BlockType::T:
            minX = 0;
            minY = 3;
            maxX = 2;
            maxY = 4;
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
tilePositions{Block::getInitialTilePositionForType(type, minX, minY, maxX, maxY)},
previousTilePositions{Block::getInitialTilePositionForType(type, minX, minY, maxX, maxY)} {}

Block::~Block() {}

void Block::moveDown() {
    for (auto& tile: tilePositions) {
        tile.first++;
    }
    ++minY;
    ++maxY;
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::moveLeft() {
    for (auto &tile: tilePositions) {
        tile.second--;
    }
    --minX;
    --maxX;
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::moveRight() {
    for (auto &tile: tilePositions) {
        tile.second++;
    }
    ++minX;
    ++maxX;
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::rotateCW() {
    int temp;
    for (auto &tile: tilePositions) {
        temp = tile.first;
        tile.first = maxY - (maxX - tile.second);
        tile.second = minX + (maxY - temp);
    }
    std::cout << maxX << ";" << maxY << ";" << minX << ";" << minY << std::endl;
    temp = maxX;
    maxX = minX + (maxY - minY);
    minY = maxY - (temp - minX);
    std::cout << maxX << ";" << minY << std::endl;
    notifyObservers();
    previousTilePositions = tilePositions;
}

void Block::rotateCCW() {
    int temp;
    for (auto &tile: tilePositions) {
        temp = tile.first;
        tile.first = maxY - (maxX - tile.second);
        tile.second = minX + (maxY - temp);
    }
    temp = maxX;
    maxX = minX + (maxY - minY);
    minY = maxY - (temp - minX);
    notifyObservers();
    previousTilePositions = tilePositions;
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

int Block::getMinX() {
    return minX;
}

int Block::getMinY() {
    return minY;
}

int Block::getMaxX() {
    return maxX;
}

int Block::getMaxY() {
    return maxY;
}
