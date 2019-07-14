#include "Engine.h"

using namespace std;

// Constructors
Engine::EngineImpl::EngineImpl(shared_ptr<Board> b, int level): 
level{level},
score{0},
highScore{0},
isGettingRandomBlocks{false},
commandTrie{nullptr},
board{b},
currentBlock{nullptr} {}

Engine::EngineImpl::~EngineImpl() {
    commandTrie.release();
}

Engine::Engine(shared_ptr<Board> b): 
impl{make_unique<EngineImpl>(b, 0)} {}
Engine::~Engine() {}

// Private method

void Engine::levelUp() {
    if (impl->level + 1 <= Engine::MAX_LEVEL) {
        ++impl->level;
    }
}

void Engine::levelDown() {
    if (impl->level - 1 >= Engine::MIN_LEVEL) {
        --impl->level;
    }
}

void Engine::processInputFile() {

}

void Engine::restart() {
    // Implement board->reset()
    impl->board->reset();
}

// Overriden methods

void Engine::notify(Subject * subject) {

}

// Public methods

void Engine::run(std::istream &in) {
    string input;
    string command;
    while (true) {
        in >> input;
        cout << "Input detected " << input << endl;
        command = input;
        // command = impl->commandTrie.interpretInput(input);
        if (command == "quit") break;
        performCommand(command);
    }
}

// requires: command is always valid, numRepititions is the number of times to perform the command
void Engine::performCommand(string command, int numRepititions) {
    if (command == "left") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptMoveLeft();
    } else if (command == "right") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptMoveRight();
    } else if (command == "down") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptMoveDown();
    } else if (command == "clockwise") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptRotateCW();
    } else if (command == "counterclockwise") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptRotateCCW();
    } else if (command == "drop") {
        for (int i = 0; i < numRepititions; ++i) impl->board->dropToBottom();
    } else if (command == "levelup") {
        for (int i = 0; i < numRepititions; ++i) levelUp();
    } else if (command == "leveldown") {
        for (int i = 0; i < numRepititions; ++i) levelDown();
    } else if (command == "norandom") {
        impl->isGettingRandomBlocks = false;
        // take input file
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptRotateCW();
    } else if (command == "random") {
        impl->isGettingRandomBlocks = true;
    } else if (command == "restart") {
        restart();
    } else if (command == "hint") {
        // Give hint
    } else {
        // TODO: Command to replace current block w block of different type

        // cast string command to I, J, and other block types
        // Assuming that the string is of length 1 
        BlockType b = static_cast<BlockType>(command.front());
        
        // Replace current block with block of this type
    }

    
    
}