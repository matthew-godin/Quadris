#include "BlockFactory.h"
#include <unordered_map>
#include <string>
#include <iostream>

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
    }

shared_ptr<Block> BlockFactory::getNextBlock() {
    BlockType blockType = BlockType::EMPTY;
    
    switch (level) {
        case 0: {
            if (inputStream.eof()) {
                inputStream.seekg(0, ios::beg);
            }
            char inputChar;
            inputStream >> inputChar;
            blockType = static_cast<BlockType>(inputChar);
            break;
        }
        case 1: {
            // BlockType blockType = 
            // return Block()
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
    }

    return make_shared<Block>(blockType);
}

void BlockFactory::incrementLevel() {
    level++;
}

void BlockFactory::decrementLevel() {
    level--;
}