#include "BlockFactory.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::ifstream;
using std::rand;
using std::unordered_map;
using std::string;
using std::ios;
using std::make_shared;
using std::shared_ptr;

const double PROBABILITY_1_12 = 1/12;
const double PROBABILITY_1_6 = 1/6;
const int NUM_BLOCK_TYPES = 7;

BlockFactory::BlockFactory(int level, string inputFile) :
    level{level},
    inputStream{ifstream(inputFile)} {
        if (!inputStream.is_open()) {
            // TODO: throw error
        }
        srand(time(0));
    }

shared_ptr<Block> BlockFactory::getNextBlock() {
    BlockType blockType = BlockType::EMPTY;
    char chosenChar;
    int randNum;
    
    switch (level) {
        case 0:
            if (inputStream.eof()) {
                inputStream.seekg(0, ios::beg);
            }
            char inputChar;
            inputStream >> inputChar;
            blockType = static_cast<BlockType>(inputChar);
            break;
        case 1:
            randNum = rand() % 12;
            if (randNum > 5) {
                if (randNum > 7) {
                    if (randNum > 9) {
                        chosenChar = 'J';
                    } else {
                        chosenChar = 'L';
                    }
                } else {
                    chosenChar = 'I';
                }
            } else {
                if (randNum > 1) {
                    if (randNum > 3) {
                        chosenChar = 'O';
                    } else {
                        chosenChar = 'T';
                    }
                } else {
                    if (randNum > 0) {
                        chosenChar = 'S';
                    } else {
                        chosenChar = 'Z';
                    }
                }
            }
            blockType = static_cast<BlockType>(chosenChar);
            break;
        case 2:
            randNum = rand() % 7;
            switch (randNum) {
                case 0:
                    chosenChar = 'S';
                    break;
                case 1:
                    chosenChar = 'Z';
                    break;
                case 2:
                    chosenChar = 'I';
                    break;
                case 3:
                    chosenChar = 'J';
                    break;
                case 4:
                    chosenChar = 'L';
                    break;
                case 5:
                    chosenChar = 'O';
                    break;
                case 6:
                    chosenChar = 'T';
                    break;
            }
            blockType = static_cast<BlockType>(chosenChar);
            break;
        case 3:
        case 4:
            randNum = rand() % 9;
            if (randNum > 3) {
                switch (randNum) {
                    case 4:
                        chosenChar = 'I';
                        break;
                    case 5:
                        chosenChar = 'J';
                        break;
                    case 6:
                        chosenChar = 'L';
                        break;
                    case 7:
                        chosenChar = 'O';
                        break;
                    case 8:
                        chosenChar = 'T';
                        break;
                }
            } else {
                if (randNum > 1) {
                    chosenChar = 'S';
                } else {
                    chosenChar = 'Z';
                }
            }
            blockType = static_cast<BlockType>(chosenChar);
            break;
    }

    return make_shared<Block>(blockType, level);
}

shared_ptr<Block> BlockFactory::getBlockOfType(BlockType type) {
    return make_shared<Block>(type, level);
}
void BlockFactory::incrementLevel() {
    level++;
}

void BlockFactory::decrementLevel() {
    level--;
}
