#pragma once
#include <SDL.h>

class Game {
public:

	Game();
	bool Initialize(); // Инициализация 
	void RunLoop(); // Игровой цикл
	void Shutdown(); // Close the app

private:
	// Вспомогательные функции для игрового цикла

	void ProcessInput();
	//void updategame(); // обновление игры 
	//void generateoutput();
	SDL_Window* mWindow; // Создание окна
	bool mIsRunning; // Проверка запуска игры

};