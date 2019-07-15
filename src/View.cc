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
    arcadeFont = NULL;
    quit = false;
    if (!init(&window, &screenSurface)) {
        errorFile.open(ERR_FILE_LOC);
        errorFile << "Failed to initialize!" << std::endl;
        errorFile.close();
    }
    else {
        if (!loadMedia(&I_Block, "../img/I.bmp") || !loadMedia(&J_Block, "../img/J.bmp") || !loadMedia(&L_Block, "../img/L.bmp") || !loadMedia(&O_Block, "../img/O.bmp") || !loadMedia(&S_Block, "../img/S.bmp") || !loadMedia(&Z_Block, "../img/Z.bmp") || !loadMedia(&T_Block, "../img/T.bmp") || !loadFont(&arcadeFont, "../fonts/arcade.ttf") || !loadMedia(&frame, "../img/frame.bmp")) {
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
    freeSurface(&frame);
    close(&window);
    //subject->detach(this);
}

void View::freeSurface(SDL_Surface **surface) {
	SDL_FreeSurface(*surface);
	*surface = NULL;
}

void View::freeFont(TTF_Font **font) {
	TTF_CloseFont(*font);
	*font = NULL;
}

void View::close(SDL_Window **window_) {
	SDL_DestroyWindow(*window_);
	*window_ = NULL;
        TTF_Quit();
	SDL_Quit();
}

bool View::init(SDL_Window **window_, SDL_Surface **screenSurface_) {
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		errorFile.open(ERR_FILE_LOC);
		errorFile << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		errorFile.close();
                success = false;
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
        if (TTF_Init() < 0) {
            errorFile.open(ERR_FILE_LOC);
	    errorFile << "SDL_TTF could not initialize! SDL_TTF_Error: " << TTF_GetError() << std::endl;
	    errorFile.close();
            success = false;
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

bool View::loadFont(TTF_Font **font, char name[]) {
	bool success = true;
	*font = TTF_OpenFont(name);
	if (*font == NULL) {
            errorFile.open(ERR_FILE_LOC);
            errorFile << "Unable to load font " << name << "! SDL Error: " << TTF_GetError() << std::endl;
            errorFile.close();
	    success = false;
	}
	return success;
}

void View::notify(Subject *subject) {
    
}

void View::notify(Engine *engine) {
    std::string level = std::string(engine->getLevel()), score = std::string(engine->getScore()), highscore = std::string(engine->getHighscore());
    int maxLength = std::max(level.size(), highscore.size());
    int length = engine->getBoardLength(), height = engine->getBoardHeight();
    std::string levelString = "Level:" + std::string(4 + maxLength - level.size(), ' ') + level, scoreString = "Score:" + std::string(4 + maxLength - score.size(), ' ') + score, highscoreString = "Hi Score:" + std::string(1 + maxLength - highscore.size(), ' ') + highscore;
    SDL_Rect partialTop, partialBottom;
    SDL_Surface *levelSurface = TTF_RenderText_Solid(arcadeFont, levelString, textColor), *scoreSurface = TTF_RenderText_Solid(arcadeFont, scoreString, textColor), *highscoreSurface = TTF_RenderText_Solid(arcadeFont, highscoreString, textColor), *nextSurface = TTF_RenderText_Solid(arcadeFont, "Next:", textColor);
    partialTop.x = 0;
    partialTop.y = 0;
    partialTop.w = 25;
    partialTop.h = 25;
    partialBottom.x = 0;
    partialBottom.y = 25;
    partialBottom.w = 25;
    partialBottom.h = 25;
    if (levelSurface == NULL || scoreSurface == NULL || highscoreSurface == NULL) {
        errorFile.open(ERR_FILE_LOC);
	errorFile << "Unable to render text surface! SDL_TTF_Error: " << TTF_GetError() << std::endl;
	errorFile.close();
    }
    SDL_FillRect(screenSurface, NULL, 0x000000);
    outStream << levelString << std::endl;
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(levelSurface, NULL, screenSurface, &position);
    outStream << scoreString << std::endl;
    position.y += 50;
    SDL_BlitSurface(scoreSurface, NULL, screenSurface, &position);
    outStream << highscoreString << std::endl;
    position.y += 50;
    SDL_BlitSurface(highscoreSurface, NULL, screenSurface, &position);
    outStream << std::string(11, '-') << std::endl;
    position.y += 50;
    SDL_BlitSurface(frame, NULL, screenSurface, &position);
    position.x += 10;
    position.y += 10;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < length; ++j) {
            switch (engine->getTypeAt(i, j)) {
                case BlockType::I:
                    outStream << "I";
                    SDL_BlitSurface(I_Block, partialTop, screenSurface, &position);
                    break;
                case BlockType::J:
                    outStream << "J";
                    SDL_BlitSurface(J_Block, partialTop, screenSurface, &position);
                    break;
                case BlockType::L:
                    outStream << "L";
                    SDL_BlitSurface(L_Block, partialBottom, screenSurface, &position);
                    break;
                case BlockType::O:
                    outStream << "O";
                    SDL_BlitSurface(O_Block, partialTop, screenSurface, &position);
                    break;
                case BlockType::S:
                    outStream << "S";
                    SDL_BlitSurface(S_Block, partialBottom, screenSurface, &position);
                    break;
                case BlockType::Z:
                    outStream << "Z";
                    SDL_BlitSurface(Z_Block, partialTop, screenSurface, &position);
                    break;
                case BlockType::T:
                    outStream << "T";
                    SDL_BlitSurface(T_Block, partialTop, screenSurface, &position);
                    break;
                case BlockType::EMPTY:
                    outStream << " ";
                    break;
            }
            position.x += 25;
        }
        outStream << std::endl;
        position.y += 25;
    }
    position.x = 0;
    position.y += 10;
    outStream << std::string(11, '-') << std::endl;
    outStream << "Next:" << std::endl;
    SDL_BlitSurface(nextSurface, NULL, screenSurface, &position);
    position.y += 50;
    switch (engine->getNextBlock()) {
        case BlockType::I:
            outStream << "IIII" << std::endl;
            SDL_BlitSurface(I_Block, NULL, screenSurface, &position);
            break;
        case BlockType::J:
            outStream << "J" << std::endl << "JJJ" << std::endl;
            SDL_BlitSurface(J_Block, NULL, screenSurface, &position);
            break;
        case BlockType::L:
            outStream << "  L" << std::endl << "LLL" << std::endl;
            SDL_BlitSurface(L_Block, NULL, screenSurface, &position);
            break;
        case BlockType::O:
            outStream << "OO" << std::endl << "OO" << std::endl;
            SDL_BlitSurface(O_Block, NULL, screenSurface, &position);
            break;
        case BlockType::S:
            outStream << " SS" << std::endl << "SS" << std::endl;
            SDL_BlitSurface(S_Block, NULL, screenSurface, &position);
            break;
        case BlockType::Z:
            outStream << "ZZ" << std::endl << " ZZ" << std::endl;
            SDL_BlitSurface(Z_Block, NULL, screenSurface, &position);
            break;
        case BlockType::T:
            outStream << "TTT" << std::endl << " T" << std::endl;
            SDL_BlitSurface(T_Block, NULL, screenSurface, &position);
            break;
    }
}
