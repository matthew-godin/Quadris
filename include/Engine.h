#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "Block.h"
#include "Observer.h"
#include "Subject.h"

class Engine: public Observer, public Subject {
    int level;
    int score;
    int highScore;
    std::vector<std::vector<int>> board;
    std::vector<Block> blocks;
    bool isGettingRandomBlocks;
    std::queue<Block> queuedBlocks;
    Block *currentBlock;

public:
    Engine();
    ~Engine();
    Engine(const Engine&);
    Engine(const Engine&&);
    Engine& operator=(const Engine&);
    Engine& operator=(const Engine&&);

    virtual void notify(Subject*) override;
    void interpretCommand(std::string);
};
#endif
