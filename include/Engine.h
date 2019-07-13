#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <map>
#include "Block.h"
#include "Observer.h"
#include "Subject.h"
#include "Board.h"
#include "CommandTrie.h"

using std::shared_ptr;
using std::unique_ptr;
using std::queue;
using std::string;
using std::unordered_map;

class Engine: public Observer, public Subject {

    struct EngineImpl {
        int level;
        int score;
        int highScore;
        bool isGettingRandomBlocks;
        CommandTrie commandTrie;
        // Main Board
        shared_ptr<Board> board;
        shared_ptr<Block> currentBlock;
        queue<Block> queuedBlocks;
    };

    unique_ptr<EngineImpl> impl;

    void levelUp();
    void levelDown();
    void processInputFile();
    void restart();
    
    public:
        Engine();
        ~Engine();
        Engine(const Engine&);
        Engine(const Engine&&);
        Engine& operator=(const Engine&);
        Engine& operator=(const Engine&&);

        void notify(Subject*) override;

        void run();
        void performCommand(string);
};

#endif
