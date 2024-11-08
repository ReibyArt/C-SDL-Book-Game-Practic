#include "Game.h"
#include <iostream>
using namespace std;



const int thickness = 20; // Wall Thickness
const float paddleH = 200.0f; // Height of Paddle
Uint32 mTicksCount = 0;
float bulletTime = 64.0f;




Game::Game(): mWindow(nullptr), mIsRunning(true) 
{
}
	// Initialize our game
bool Game::Initialize() {


	
	int sdlResault = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResault != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError);
		return false;
	}
	mWindow = SDL_CreateWindow("My First SDL Game", 100, 100, 1024, 768, 0);
	if (!mWindow) {
		SDL_Log("Falied to create window: %s", SDL_GetError);
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Создать окно и Использовать ускорение и VSYNC


	// Origin Position Of Paddle and Ball
	mPaddlePos.x = 20.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
}


// Event keyboard
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
	const Uint8* state = SDL_GetKeyboardState(NULL); // ПОЛУЧАЕМ СОСТОЯНИЕ КЛАВИАТУРЫ МАССИВ КАКАЯ КНОПКА НАЖАТА

	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	// Direction our paddle //
	if (state[SDL_SCANCODE_W]) {
		mPaddleDir = mPaddleDir - 1.0f;
	}
	if (state[SDL_SCANCODE_S]) {
		mPaddleDir = mPaddleDir + 1.0f;
	}
}


// Update Game //
void Game::UpdateGame()
{
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// std::cout << "Current Frame From DeltaTime-> " << deltaTime << std::endl;
	mTicksCount = SDL_GetTicks();

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + bulletTime));
	{
		// std::cout << "tick in while " << mTicksCount << std::endl;
	}
	if (deltaTime > 0.5f) {
		deltaTime = 0.5f;
	}
	// Paddle Dir
	if (mPaddleDir != 0) {
		mPaddlePos.y = mPaddleDir * 300.0f * deltaTime;
	}
	std::cout << "Current PaddlePosY -> " << mPaddlePos.y << std::endl;

	// Check Paddle Screen!

	if (mPaddlePos.y > 768.0f - thickness) {
		std::cout << "More than screen!" << std::endl;
	}


	// Check paddle collider ))
	if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
		mPaddlePos.y = paddleH / 2.0f + thickness;
	}

	else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
		mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
	}
	

	
}


// Main Game Loop
void Game::RunLoop() {

	while (mIsRunning) {
		ProcessInput();
		 UpdateGame();
		GenerateOutput();
	}
}

// Render
void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0,0,255,255);
	// Clear back buffer
	SDL_RenderClear(mRenderer); 
	// Отрисовка кантика (стены) по периметру экрана
	
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	// Верхняя стена
	SDL_Rect wall{ 0,0,1024,thickness }; 
	SDL_RenderFillRect(mRenderer, &wall);
	// Нижняя стена
	wall.y = 768 - thickness; 
	SDL_RenderFillRect(mRenderer, &wall);
	// Правая стена
	wall.x = 1024 - thickness;
	wall.w = thickness;
	wall.h = 1024;
	wall.y = 0;
	SDL_RenderFillRect(mRenderer, &wall);


	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // цвет для мяча
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // цвет для ракетки
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};

	SDL_RenderFillRect(mRenderer, &paddle);
	

	// Swap buffer
	SDL_RenderPresent(mRenderer);
	
}



// Close Window
void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
 


