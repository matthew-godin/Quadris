#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "Engine.h"
#include "Board.h"
#include "View.h"

using std::ostream;
using std::shared_ptr;
using std::string;

class Game {
    // Model
    shared_ptr<Board> board;
    // Controller
    shared_ptr<Engine> engine;
    // View
    shared_ptr<View> view;

public:
    Game(int, string);
    ~Game();

    void start();

    friend ostream& operator<<(ostream&, const Game& game);
};

#endif
