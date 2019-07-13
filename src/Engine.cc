#include "Engine.h"

using namespace std;

Engine::Engine() {}
Engine::~Engine() {}

void Engine::notify(Subject * subject) override {
    
}

void Engine::run() {
    string input;
    string command;
    while (true) {
        cin >> input;
        command = impl.commandTrie.interpretInput(input);
        performCommand(command);
    }
}

void Engine::performCommand(string command) {
}