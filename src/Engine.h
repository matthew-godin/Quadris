#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>

class Engine {
    int level;
public:
    Engine();
    ~Engine();
    Engine(const Engine&);
    Engine(const Engine&&);
    Engine& operator=(const Engine&);
    Engine& operator=(const Engine&&);
};
#endif
