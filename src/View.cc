#include "../include/View.h"

View::View(std::ostream &sout) : outStream{sout} {
    
    window = NULL;
    screenSurface = NULL;
    I_Block = NULL;
    J_Block = NULL;
    L_Block = NULL;
    O_Block = NULL;
    S_Block = NULL;
    Z_Block = NULL;
    T_Block = NULL;
    quit = false;
    if (!init(&window, &screenSurface)) {
        errorFile.open(ERR_FILE_LOC);
        errorFile << "Failed to initialize!" << std::endl;
        errorFile.close();
    }
    else {
        if (!loadMedia(&I_Block, "../img/I.bmp") || !loadMedia(&J_Block, "../img/J.bmp") || !loadMedia(&L_Block, "../img/L.bmp") || !loadMedia(&O_Block, "../img/O.bmp") || !loadMedia(&S_Block, "../img/S.bmp") || !loadMedia(&Z_Block, "../img/Z.bmp") || !loadMedia(&T_Block, "../img/T.bmp")) {
            errorFile.open(ERR_FILE_LOC);
            errorFile << "Failed to load media!" << std::endl;
            errorFile.close();
        }
        else {
            position.x = 25;
            position.y = 25;
            SDL_BlitSurface(I_Block, NULL, screenSurface, &position);
            position.x = 150;
            position.y = 25;
            SDL_BlitSurface(J_Block, NULL, screenSurface, &position);
            position.x = 25;
            position.y = 150;
            SDL_BlitSurface(L_Block, NULL, screenSurface, &position);
            position.x = 150;
            position.y = 150;
            SDL_BlitSurface(O_Block, NULL, screenSurface, &position);
            position.x = 275;
            position.y = 25;
            SDL_BlitSurface(S_Block, NULL, screenSurface, &position);
            position.x = 275;
            position.y = 150;
            SDL_BlitSurface(Z_Block, NULL, screenSurface, &position);
            position.x = 25;
            position.y = 275;
            SDL_BlitSurface(T_Block, NULL, screenSurface, &position);
            SDL_UpdateWindowSurface(window);
        }
    }
}

View::~View() {
    freeSurface(&I_Block);
    freeSurface(&J_Block);
    freeSurface(&L_Block);
    freeSurface(&O_Block);
    freeSurface(&S_Block);
    freeSurface(&Z_Block);
    freeSurface(&T_Block);
    close(&window);
    //subject->detach(this);
}

void View::freeSurface(SDL_Surface **surface) {
	SDL_FreeSurface(*surface);
	*surface = NULL;
}

void View::close(SDL_Window **window_) {
	SDL_DestroyWindow(*window_);
	*window_ = NULL;
	SDL_Quit();
}

bool View::init(SDL_Window **window_, SDL_Surface **screenSurface_) {
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		errorFile.open(ERR_FILE_LOC);
		errorFile << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		errorFile.close();
	}
	else
	{
		*window_ = SDL_CreateWindow("Quadris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(*window_ == NULL)
		{
                        errorFile.open(ERR_FILE_LOC);
			errorFile << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                        errorFile.close();
			success = false;		
		}
		else
		{
			*screenSurface_ = SDL_GetWindowSurface(*window_);
		}
	}
	return success;
}

bool View::loadMedia(SDL_Surface **surface, char name[]) {
	bool success = true;
	*surface = SDL_LoadBMP(name);
	if (*surface == NULL) {
            errorFile.open(ERR_FILE_LOC);
            errorFile << "Unable to load image " << name << "! SDL Error: " << SDL_GetError() << std::endl;
            errorFile.close();
	    success = false;	
	}
	return success;
}

void View::notify(Subject *subject) {
  
}
