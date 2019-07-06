#include "../include/Observer.h"
#include "../include/Engine.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {
    bool isText = false;
    float seed = 0.0;
    string scriptFile = "";
    int startLevel = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-text") == 0) {
                cout << "Text mode on" << endl;
                isText = true;
            } else if (strcmp(argv[i], "-seed") == 0) {
                try {
                    string seedString = string(argv[i + 1]);
                    seed = stof(seedString);
                    i++;
                    cout << "Random seed provided: " << seed << endl;
                } catch (...) {
                    cerr << "Failed to parse argument -seed" << endl;
                }
            } else if (strcmp(argv[i], "-scriptfile") == 0) {
                try {
                    string fileName = string(argv[i + 1]);
                    i++;
                    cout << "file name provided: " << fileName << endl;
                } catch (...) {
                    cerr << "Failed to parse argument -scriptfile" << endl;
                }
            } else if (strcmp(argv[i], "-startlevel") == 0) {
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

    return 0;
}