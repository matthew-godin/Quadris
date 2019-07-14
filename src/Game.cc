#include "Game.h"

using std::make_shared;
using std::istream;

Game::Game(): 
board{make_shared<Board>()}, 
engine{make_shared<Engine>(board)} {

}

Game::~Game() {
    board.reset();
    engine.reset();
    view.reset();
}

void Game::start(std::istream& inputStream) {
    engine->run(inputStream);
}

ostream& operator<<(ostream& out, const Game& game) {
    out << *game.board;
    return out;
}