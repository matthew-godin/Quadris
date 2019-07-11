#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include "Block.h"
#include "Observer.h"
#include "Subject.h"
#include "Board.h"

using std::shared_ptr;
using std::unique_ptr;
using std::queue;
using std:: string;

struct EngineImpl {
    int level;
    int score;
    int highScore;
    bool isGettingRandomBlocks;
    // Main Board
    shared_ptr<Board> board;
    shared_ptr<Block> currentBlock;
    queue<Block> queuedBlocks;
};

class Engine: public Observer, public Subject {
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

    virtual void notify(Subject*) override;
    void interpretCommand(string);
};

#endif
