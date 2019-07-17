#ifndef BLOCK_FACTORY_H_
#define BLOCK_FACTORY_H_

#include <fstream>
#include <string>
#include <memory>
#include "Block.h"

using std::ifstream;
using std::string;
using std::shared_ptr;

class Block;

class BlockFactory {
    int level;
    ifstream inputStream;
    public:
        BlockFactory(int, string);
        shared_ptr<Block> getNextBlock();
        shared_ptr<Block> getBlockOfType(BlockType);
        void incrementLevel();
        void decrementLevel();
};

#endif