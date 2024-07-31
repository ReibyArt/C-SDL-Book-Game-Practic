#include "Game.h"
#include <iostream>
using namespace std;
//#include <SDL.h>


	
Game::Game():mWindow(nullptr), mIsRunning(true) 
{
}
	
bool Game::Initialize() {
	
	int sdlResault = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResault != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError);
		return false;
	}
	mWindow = SDL_CreateWindow("My First SDL Game", 100,100,1024, 768, 0);
	if (!mWindow) {
		SDL_Log("Falied to create window: %s", SDL_GetError);
		return false;
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL); // œŒÀ”◊¿≈Ã —Œ—“ŒﬂÕ»≈  À¿¬»¿“”–€ Ã¿——»¬  ¿ ¿ﬂ  ÕŒœ ¿ Õ¿∆¿“¿
	cout << state << endl;

	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
void Game::RunLoop() {

	while (mIsRunning) {
		ProcessInput();
		/*UpdateGame();
		GenerateOutput();*/
	}
}

