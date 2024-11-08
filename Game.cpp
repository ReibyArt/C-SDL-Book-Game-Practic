#include "Game.h"
#include <iostream>
using namespace std;



const int thickness = 10; // Wall Thickness
const float paddleH = 100; // Height of Paddle
Uint32 mTicksCount = 0;
float frameTime = 16.0f;


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
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	
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

	if(state != NULL) {
		if (state[SDL_SCANCODE_ESCAPE]) {
			mIsRunning = false;
		}

		// Direction our paddle UP DOWN //
		if (state[SDL_SCANCODE_W]) {
			mPaddleDir = mPaddleDir - 1.0f;
		}
		if (state[SDL_SCANCODE_S]) {
			mPaddleDir = mPaddleDir + 1.0f;
		}
	}
	
}


// Update Game //
void Game::UpdateGame()
{
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// std::cout << "Current Frame From DeltaTime-> " << deltaTime << std::endl;
	mTicksCount = SDL_GetTicks();

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + frameTime));
	{
		// std::cout << "tick in while " << mTicksCount << std::endl;
	}
	if (deltaTime > 0.5f) {
		deltaTime = 0.5f;
	}
	// Paddle Dir
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
	}
	 // std::cout << "Current PaddlePosY -> " << mPaddlePos.y << std::endl;


	// Check paddle collider wall ))

	if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
		mPaddlePos.y = paddleH / 2.0f + thickness;
	}

	else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
		
		mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
	}

	// Update Ball Position
	float diff = mBallPos.y - mPaddlePos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;
	// std::cout << "Current PosBall -> " << mBallPos.x << std::endl;

	if (mBallPos.y <= thickness && mBallVel.y < 0.0f) {
		mBallVel.y = mBallVel.y * -1;
	}
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Game Over - Пиксель упущен))
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// Удар в правую стену
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// Удар в верхнюю стену
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Удар в нижнюю стену
	else if (mBallPos.y >= (768 - thickness) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
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
 


