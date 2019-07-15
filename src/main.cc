#include "../include/Observer.h"
#include "../include/Game.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {
    
    bool isText = false;
    float seed = 0.0;

    int startLevel = 0;
    string scriptFile = "sequence.txt";

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
			string argument = string(argv[i]);
            if (argument == "-text") {
                isText = true;
                cout << "Text mode is on" << endl;
            } else if (argument == "-seed") {
                try {
                    string seedString = string(argv[i + 1]);
                    seed = stof(seedString);
                    i++;
                    cout << "Random seed provided: " << seed << endl;
                } catch (...) {
                    cerr << "Failed to parse argument -seed" << endl;
                }
            } else if (argument == "-scriptfile") {
                try {
                    string fileName = string(argv[i + 1]);
                    i++;
                    cout << "file name provided: " << fileName << endl;
                } catch (...) {
                    cerr << "Failed to parse argument -scriptfile" << endl;
                }
            } else if (argument == "-startlevel") {
                try {
                    string levelNumber = string(argv[i + 1]);
                    startLevel = stoi(levelNumber);
                    i++;
                    cout << "Start level number: " << startLevel << endl;
                } catch (...) {
                    cerr << "Failed to parse argument -startlevel" << endl;
                }
            }
        }
    }

    Game game(startLevel, scriptFile);
    game.start();

    return 0;
}
