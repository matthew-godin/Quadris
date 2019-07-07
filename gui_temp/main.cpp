#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
bool init(SDL_Window **window, SDL_Surface **screenSurface);
bool loadMedia(SDL_Surface **surface, char name[]);
void freeSurface(SDL_Surface **surface);
void close(SDL_Window **window);

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Surface *screenSurface = NULL, *I_Block = NULL, *J_Block = NULL, *L_Block = NULL, *O_Block = NULL, *S_Block = NULL, *Z_Block = NULL, *T_Block = NULL;
	SDL_Rect position;
	bool quit = false;
	SDL_Event e;
	if (!init(&window, &screenSurface)) {
		cerr << "Failed to initialize!" << endl;
	}
	else {
		if (!loadMedia(&I_Block, "I.bmp") || !loadMedia(&J_Block, "J.bmp") || !loadMedia(&L_Block, "L.bmp") || !loadMedia(&O_Block, "O.bmp") || !loadMedia(&S_Block, "S.bmp") || !loadMedia(&Z_Block, "Z.bmp") || !loadMedia(&T_Block, "T.bmp")) {
			cerr << "Failed to load media!" << endl;
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
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_UpdateWindowSurface(window);
	}
	freeSurface(&I_Block);
	freeSurface(&J_Block);
	freeSurface(&L_Block);
	freeSurface(&O_Block);
	freeSurface(&S_Block);
	freeSurface(&Z_Block);
	freeSurface(&T_Block);
	close(&window);
	return 0;
}

bool init(SDL_Window **window, SDL_Surface **screenSurface) {
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
	}
	else
	{
		*window = SDL_CreateWindow("Quadris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(*window == NULL)
		{
			cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;		
		}
		else
		{
			*screenSurface = SDL_GetWindowSurface(*window);
		}
	}
	return success;
}

bool loadMedia(SDL_Surface **surface, char name[]) {
	bool success = true;
	*surface = SDL_LoadBMP(name);
	if (*surface == NULL) {
		cerr << "Unable to load image " << name << "! SDL Error: " << SDL_GetError() << endl;
		success = false;	
	}
	return success;
}

void freeSurface(SDL_Surface **surface) {
	SDL_FreeSurface(*surface);
	*surface = NULL;
}

void close(SDL_Window **window) {
	SDL_DestroyWindow(*window);
	*window = NULL;
	SDL_Quit();
}
