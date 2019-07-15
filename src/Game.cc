#include "Game.h"

using std::make_shared;
using std::istream;

Game::Game(int level, string inputFile) : 
    view{make_shared<View>()},
    board{make_shared<Board>()}, 
    engine{make_shared<Engine>(board, view, level, inputFile)} {}

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