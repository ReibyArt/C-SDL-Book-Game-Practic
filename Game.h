#pragma once
#include <SDL.h>


// Хранение координат для мяча и ракетки
struct Vector2
{
	float x;
	float y;
};

// Главный Игровой Класс
class Game 
{
public:

	Game();
	bool Initialize(); // Инициализация 
	void RunLoop(); // Игровой цикл
	void Shutdown(); // Close the app

private:
	// Вспомогательные функции для игрового цикла
	void ProcessInput();
	void UpdateGame();
	

	void GenerateOutput();


	SDL_Window* mWindow; // Создание окна
	SDL_Renderer* mRenderer; // Создание Рендера
	bool mIsRunning; // Проверка запуска игры

	// Позиция мяча и ракетки
	Vector2 mBallPos;
	Vector2 mPaddlePos;
	float mPaddleDir = 0.0f;
	Vector2 mBallVel; 
	
	
};