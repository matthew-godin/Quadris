#include "Engine.h"
#include <iostream>
#include <cctype>
#include <SDL2/SDL.h>

using namespace std;

// Constructors
Engine::Engine(shared_ptr<Board> b, int level, string inputFile): 
    impl{make_unique<EngineImpl>(b, level, inputFile)} {}

Engine::~Engine() {}

Engine::EngineImpl::EngineImpl(shared_ptr<Board> b, int level, string inputFile): 
    level{level},
    score{0},
    highScore{0},
    isGettingRandomBlocks{false},
    isGameOver{false},
    blockFactory{BlockFactory(level, inputFile)},
    commandTrie{nullptr},
    board{b},
    currentBlock{nullptr} {}

Engine::EngineImpl::~EngineImpl() {
    commandTrie.release();
}

// Private methods
// requires: command is always valid, numRepititions is the number of times to perform the command
void Engine::performCommand(string command, int numRepititions) {
    if (command == "left") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptMoveLeft();
    } else if (command == "right") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptMoveRight();
    } else if (command == "down") {
        for (int i = 0; i < numRepititions; ++i) {
            bool blockCanMoveDownAgain = impl->board->moveDown();
            if (!blockCanMoveDownAgain) {
                bool wasInsertSuccessful = impl->board->attemptInsertBlockIntoBoard(impl->blockFactory.getNextBlock());
                impl->board->checkForFilledRow();
                if (!wasInsertSuccessful) {
                    impl->isGameOver = true;
                }
            }
        }
    } else if (command == "clockwise") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptRotateCW();
    } else if (command == "counterclockwise") {
        for (int i = 0; i < numRepititions; ++i) impl->board->attemptRotateCCW();
    } else if (command == "drop") {
        for (int i = 0; i < numRepititions; ++i) {
            impl->board->dropToBottom();
            bool wasInsertSuccessful = impl->board->attemptInsertBlockIntoBoard(impl->blockFactory.getNextBlock());
            impl->board->checkForFilledRow();
            if (!wasInsertSuccessful) {
                impl->isGameOver = true;
            }
        }
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
        // BlockType b = static_cast<BlockType>(command.front());
        
        // Replace current block with block of this type
    }
}

void Engine::levelUp() {
    if (impl->level + 1 <= Engine::MAX_LEVEL) {
        ++impl->level;
        impl->blockFactory.incrementLevel();
    }
}

void Engine::levelDown() {
    if (impl->level - 1 >= Engine::MIN_LEVEL) {
        --impl->level;
        impl->blockFactory.decrementLevel();
    }
}

void Engine::restart() {
    // Implement board->reset()
    impl->board->reset();
    // Reset score
}

// Overriden methods
void Engine::notify(Subject* subject) {

}

// Public methods
void Engine::run() {
    string input;
    string command;
    SDL_Event e;
    // Insert the first block in the board
    impl->board->attemptInsertBlockIntoBoard(impl->blockFactory.getNextBlock());
    notifyObservers();
    while (true) {
        bool wasGameClosed = false;
        // Loop that checks if the game is closed by user
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
               wasGameClosed = true;
               break;
            }
        }
        
        if (wasGameClosed) break;

        // checks if game is over and closes the game
        if (impl->isGameOver) {
            std::cout << "GAME OVER" << std::endl;
            break;
        }

        // Otherwise take input from user
        cin >> input;

        int i;
        for (i = 0; i < input.size(); i++) {
            if (!isdigit(input.at(i))) break;
        }

        int numRepititions = input.substr(0, i).size() > 0 ? stoi(input.substr(0, i)) : 1;
        input = input.substr(i, input.size() - i);
        
        command = input; // impl->commandTrie.interpretInput(input);

        

        if (command == "quit") {
            break;
        }
        performCommand(command, numRepititions);
        notifyObservers();
    }
}

int Engine::getLevel() {
    return impl->level;
}

int Engine::getScore() {
    return impl->score;
}

int Engine::getHighscore() {
    return impl->highScore;
}

BlockType Engine::getTypeAt(int i, int j) {
    return impl->board->getTypeAt(i, j);
}

int Engine::getBoardLength() {
    return impl->board->getBoardLength();
}

int Engine::getBoardHeight() {
    return impl->board->getBoardHeight();
}

BlockType Engine::getNextBlock() {
    return impl->board->getNextBlock();
}

bool Engine::getGameOver() {
    return impl->isGameOver;
}
