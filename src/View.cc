#include "../include/View.h"
#include <iostream>

using std::ostream;
using std::string;

View::View(ostream &sout, Engine *engine): 
outStream{sout},
screenSurface{nullptr},
I_Block{nullptr},
J_Block{nullptr},
L_Block{nullptr},
O_Block{nullptr},
S_Block{nullptr},
Z_Block{nullptr},
T_Block{nullptr},
Star_Block{nullptr},
arcadeFont{nullptr},
window{nullptr},
quit{false} {
    engine->attach(this);
    if (!init(&window, &screenSurface)) {
        errorFile.open(ERR_FILE_LOC, std::ios_base::app);
        errorFile << "Failed to initialize view!" << std::endl;
        errorFile.close();
    } else {
        bool couldNotLoadMedia = !loadMedia(&I_Block, "img/I.bmp") || 
            !loadMedia(&J_Block, "img/J.bmp") || 
            !loadMedia(&L_Block, "img/L.bmp") || 
            !loadMedia(&O_Block, "img/O.bmp") || 
            !loadMedia(&S_Block, "img/S.bmp") || 
            !loadMedia(&Z_Block, "img/Z.bmp") ||
            !loadMedia(&T_Block, "img/T.bmp") ||
            !loadMedia(&Star_Block, "img/star.bmp") ||
            !loadFont(&arcadeFont, "fonts/arcade.ttf", 80) ||
            !loadMedia(&frame, "img/frame.bmp");
        
        if (couldNotLoadMedia) {
            errorFile.open(ERR_FILE_LOC, std::ios_base::app);
            errorFile << "Failed to load media!" << std::endl;
            errorFile.close();
        } else {
            SDL_Surface *levelSurface = TTF_RenderText_Solid(arcadeFont, "Level:", textColor);
            SDL_Surface *scoreSurface = TTF_RenderText_Solid(arcadeFont, "Score:", textColor);
            SDL_Surface *highscoreSurface = TTF_RenderText_Solid(arcadeFont, "Highscore:", textColor);
            SDL_Surface *nextSurface = TTF_RenderText_Solid(arcadeFont, "Next:", textColor);
            
            if (levelSurface == nullptr || scoreSurface == nullptr || highscoreSurface == nullptr) {
                errorFile.open(ERR_FILE_LOC);
                errorFile << "Unable to render text surface! SDL_TTF_Error: " << TTF_GetError() << std::endl;
                errorFile.close();
            }

            outStream << "Level:" << std::endl;
            position.x = 0;
            position.y = 0;
            SDL_BlitSurface(levelSurface, nullptr, screenSurface, &position);
            outStream << "Score:" << std::endl;
            position.y += 50;
            SDL_BlitSurface(scoreSurface, nullptr, screenSurface, &position);
            outStream << "Highscore:" << std::endl;
            position.y += 50;
            SDL_BlitSurface(highscoreSurface, nullptr, screenSurface, &position);
            outStream << std::string(11, '-') << std::endl;
            position.y += 50;
            SDL_BlitSurface(frame, nullptr, screenSurface, &position);
            position.x += 10;
            position.y += 10;
            outStream << std::string(18, '\n');
            outStream << std::string(11, '-') << std::endl;
            position.x -= 10;
            position.y += 450;
            outStream << "Next:" << std::endl;
            SDL_BlitSurface(nextSurface, nullptr, screenSurface, &position);
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
    freeSurface(&Star_Block);
    freeSurface(&frame);
    close(&window);
    //subject->detach(this);
}

void View::freeSurface(SDL_Surface **surface) {
	SDL_FreeSurface(*surface);
	*surface = nullptr;
}

void View::freeFont(TTF_Font **font) {
	TTF_CloseFont(*font);
	*font = nullptr;
}

void View::close(SDL_Window **window_) {
	SDL_DestroyWindow(*window_);
	*window_ = nullptr;
    TTF_Quit();
	SDL_Quit();
}

bool View::init(SDL_Window **window_, SDL_Surface **screenSurface_) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		errorFile.open(ERR_FILE_LOC, std::ios_base::app);
		errorFile << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		errorFile.close();
        success = false;
	} else {
		*window_ = SDL_CreateWindow("Quadris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (*window_ == nullptr) {
            errorFile.open(ERR_FILE_LOC, std::ios_base::app);
			errorFile << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                        errorFile.close();
			success = false;		
		} else {
			*screenSurface_ = SDL_GetWindowSurface(*window_);
		}
	}
    
    if (TTF_Init() < 0) {
        errorFile.open(ERR_FILE_LOC, std::ios_base::app);
        errorFile << "SDL_TTF could not initialize! SDL_TTF_Error: " << TTF_GetError() << std::endl;
        errorFile.close();
        success = false;
    }

	return success;
}

bool View::loadMedia(SDL_Surface **surface, char name[]) {
	bool success = true;
	*surface = SDL_LoadBMP(name);
	if (*surface == nullptr) {
        errorFile.open(ERR_FILE_LOC, std::ios_base::app);
        errorFile << "Unable to load image " << name << "! SDL Error: " << SDL_GetError() << std::endl;
        errorFile.close();
	    success = false;
	}
	return success;
}

bool View::loadFont(TTF_Font **font, char name[], int size) {
	bool success = true;
	*font = TTF_OpenFont(name, size);
	if (*font == nullptr) {
        errorFile.open(ERR_FILE_LOC, std::ios_base::app);
        errorFile << "Unable to load font " << name << "! SDL Error: " << TTF_GetError() << std::endl;
        errorFile.close();
	    success = false;
	}
	return success;
}

void View::notify(Subject *subject) {
    Engine* engine = dynamic_cast<Engine*>(subject);
    notify(engine);
}

void View::notify(Engine *engine) {
    if (engine->getGameOver()) {
         SDL_Surface *gameOverSurface = TTF_RenderText_Solid(arcadeFont, "Game Over", textColor);
         position.x = SCREEN_WIDTH / 2 - gameOverSurface->w / 2;
         position.y = SCREEN_HEIGHT / 2 - gameOverSurface->h / 2;
         SDL_BlitSurface(gameOverSurface, nullptr, screenSurface, &position);
         SDL_UpdateWindowSurface(window);
         SDL_Delay(2000);
         return;
    }
    int centerX = SCREEN_WIDTH / 2 - 295 / 2;
    string level = std::to_string(engine->getLevel());
    string score = std::to_string(engine->getScore());
    string highscore = std::to_string(engine->getHighscore());

    int maxLength = std::max(level.size(), highscore.size());
    int length = engine->getBoardLength(), height = engine->getBoardHeight();
    string levelString = "Level:" + string(4 + maxLength - level.size(), ' ') + level;
    string scoreString = "Score:" + string(4 + maxLength - score.size(), ' ') + score;
    string highscoreString = "Hi Score:" + string(1 + maxLength - highscore.size(), ' ') + highscore;
    
    SDL_Rect partialTop, partialBottom;
    SDL_Surface *levelSurface = TTF_RenderText_Solid(arcadeFont, levelString.c_str(), textColor);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(arcadeFont, scoreString.c_str(), textColor);
    SDL_Surface *highscoreSurface = TTF_RenderText_Solid(arcadeFont, highscoreString.c_str(), textColor);
    SDL_Surface *nextSurface = TTF_RenderText_Solid(arcadeFont, "Next:", textColor);

    partialTop.x = 0;
    partialTop.y = 0;
    partialTop.w = 25;
    partialTop.h = 25;
    partialBottom.x = 0;
    partialBottom.y = 25;
    partialBottom.w = 25;
    partialBottom.h = 25;
    if (levelSurface == nullptr || scoreSurface == nullptr || highscoreSurface == nullptr) {
        errorFile.open(ERR_FILE_LOC);
        errorFile << "Unable to render text surface! SDL_TTF_Error: " << TTF_GetError() << std::endl;
        errorFile.close();
    }
    SDL_FillRect(screenSurface, nullptr, 0x000000);
    outStream << levelString << std::endl;
    position.x = centerX;
    position.y = 0;
    SDL_BlitSurface(levelSurface, nullptr, screenSurface, &position);
    outStream << scoreString << std::endl;
    position.y += 50;
    SDL_BlitSurface(scoreSurface, nullptr, screenSurface, &position);
    outStream << highscoreString << std::endl;
    position.y += 50;
    SDL_BlitSurface(highscoreSurface, nullptr, screenSurface, &position);
    outStream << std::string(11, '-') << std::endl;
    position.y += 50;
    SDL_BlitSurface(frame, nullptr, screenSurface, &position);
    position.x += 10;
    position.y += 10;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < length; ++j) {
            switch (engine->getTypeAt(i, j)) {
                case BlockType::I:
                    outStream << "I";
                    SDL_BlitSurface(I_Block, &partialTop, screenSurface, &position);
                    break;
                case BlockType::J:
                    outStream << "J";
                    SDL_BlitSurface(J_Block, &partialTop, screenSurface, &position);
                    break;
                case BlockType::L:
                    outStream << "L";
                    SDL_BlitSurface(L_Block, &partialBottom, screenSurface, &position);
                    break;
                case BlockType::O:
                    outStream << "O";
                    SDL_BlitSurface(O_Block, &partialTop, screenSurface, &position);
                    break;
                case BlockType::S:
                    outStream << "S";
                    SDL_BlitSurface(S_Block, &partialBottom, screenSurface, &position);
                    break;
                case BlockType::Z:
                    outStream << "Z";
                    SDL_BlitSurface(Z_Block, &partialTop, screenSurface, &position);
                    break;
                case BlockType::T:
                    outStream << "T";
                    SDL_BlitSurface(T_Block, &partialTop, screenSurface, &position);
                    break;
                case BlockType::STAR:
                    outStream << "*";
                    SDL_BlitSurface(Star_Block, &partialTop, screenSurface, &position);
                    break;
                case BlockType::EMPTY:
                    outStream << " ";
                    break;
            }
            position.x += 25;
        }
        outStream << std::endl;
        position.x = 10 + centerX;
        position.y += 25;
    }
    position.x = centerX;
    position.y += 10;
    outStream << std::string(11, '-') << std::endl;
    outStream << "Next:" << std::endl;
    SDL_BlitSurface(nextSurface, nullptr, screenSurface, &position);
    position.y += 50;
    switch (engine->getNextBlock()) {
        case BlockType::I:
            outStream << "IIII" << std::endl;
            SDL_BlitSurface(I_Block, nullptr, screenSurface, &position);
            break;
        case BlockType::J:
            outStream << "J" << std::endl << "JJJ" << std::endl;
            SDL_BlitSurface(J_Block, nullptr, screenSurface, &position);
            break;
        case BlockType::L:
            outStream << "  L" << std::endl << "LLL" << std::endl;
            SDL_BlitSurface(L_Block, nullptr, screenSurface, &position);
            break;
        case BlockType::O:
            outStream << "OO" << std::endl << "OO" << std::endl;
            SDL_BlitSurface(O_Block, nullptr, screenSurface, &position);
            break;
        case BlockType::S:
            outStream << " SS" << std::endl << "SS" << std::endl;
            SDL_BlitSurface(S_Block, nullptr, screenSurface, &position);
            break;
        case BlockType::Z:
            outStream << "ZZ" << std::endl << " ZZ" << std::endl;
            SDL_BlitSurface(Z_Block, nullptr, screenSurface, &position);
            break;
        case BlockType::T:
            outStream << "TTT" << std::endl << " T" << std::endl;
            SDL_BlitSurface(T_Block, nullptr, screenSurface, &position);
            break;
    }
    SDL_UpdateWindowSurface(window);
}
