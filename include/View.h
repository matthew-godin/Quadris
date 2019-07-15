#ifndef VIEW_H_
#define VIEW_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <fstream>
#include <algorithm>
#include "../include/Observer.h"
#include "../include/Block.h"
#include "../include/View.h"
#include "../include/Engine.h"
class Subject;
class View : public Observer {
    std::ostream &outStream;
    std::ofstream errorFile;
    const std::string ERR_FILE_LOC = "../logs/errors.log";
    bool init(SDL_Window **window, SDL_Surface **screenSurface);
    bool loadMedia(SDL_Surface **surface, char name[]);
    bool loadFont(TTF_Font **font, char name[]);
    void freeSurface(SDL_Surface **surface);
    void freeFont(TTF_Font **font);
    void close(SDL_Window **window);
    const int SCREEN_WIDTH = 500;
    const int SCREEN_HEIGHT = 800;
    SDL_Surface *screenSurface;
    SDL_Surface *I_Block;
    SDL_Surface *J_Block;
    SDL_Surface *L_Block;
    SDL_Surface *O_Block;
    SDL_Surface *S_Block;
    SDL_Surface *Z_Block;
    SDL_Surface *T_Block;
    SDL_Surface *frame;
    TTF_Font *arcadeFont;
    SDL_Rect position;
    SDL_Color textColor = {45, 56, 34}
  public:
    SDL_Window* window;
    bool quit;
    SDL_Event e;
    View(std::ostream &);
    void notify(Subject*) override;
    void notify(Engine*);
    ~View();
};

#endif
