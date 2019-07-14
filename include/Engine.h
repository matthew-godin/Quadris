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
    static const size_t MIN_LEVEL = 0;
    static const size_t MAX_LEVEL = 4;
    struct EngineImpl {
        int level;
        int score;
        int highScore;
        bool isGettingRandomBlocks;
        unique_ptr<CommandTrie> commandTrie;
        // Main Board
        shared_ptr<Board> board;
        shared_ptr<Block> currentBlock;
        queue<shared_ptr<Block>> queuedBlocks;

        EngineImpl(shared_ptr<Board> b, int level = 0);
        ~EngineImpl();
    };

    unique_ptr<EngineImpl> impl;

    void levelUp();
    void levelDown();
    void processInputFile();
    void restart();
    
    public:
        Engine(shared_ptr<Board>);
        ~Engine();
        Engine(const Engine&);
        Engine(const Engine&&);
        Engine& operator=(const Engine&);
        Engine& operator=(const Engine&&);

        void notify(Subject*) override;

        void run(std::istream&);
        void performCommand(string command, int numRepititions = 1);
};

#endif
