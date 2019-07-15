To install SDL2 and SDL_TTF2 on Ubuntu:
sudo apt-cache search libsdl2
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev

(please check online for different OS)

To compile:
g++ main.cpp -w -lSDL2 -o main
