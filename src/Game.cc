#include "Game.h"

using std::make_shared;
using std::istream;

Game::Game(int level, string inputFile) : 
    board{make_shared<Board>()}, 
    engine{make_shared<Engine>(board, level, inputFile)},
    view{make_shared<View>(std::cout, engine.get())} {}

Game::~Game() {
    board.reset();
    engine.reset();
    view.reset();
}

void Game::start() {
    engine->run();
}

ostream& operator<<(ostream& out, const Game& game) {
    out << *game.board;
    return out;
}
