#ifndef VIEW_H_
#define VIEW_H_
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include "../include/Observer.h"
#include "../include/Block.h"
#include "../include/View.h"
class Subject;
class View : public Observer {
    std::ostream &outStream;
    std::ofstream errorFile;
    const std::string ERR_FILE_LOC = "../logs/errors.log";
    bool init(SDL_Window **window, SDL_Surface **screenSurface);
    bool loadMedia(SDL_Surface **surface, char name[]);
    void freeSurface(SDL_Surface **surface);
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
    SDL_Rect position;
  public:
    SDL_Window* window;
    bool quit;
    SDL_Event e;
    View(std::ostream &);
    void notify(Subject*) override;
    ~View();
};

#endif
