#pragma once
#include <SDL.h>

class Game {
public:

	Game();
	bool Initialize(); // ������������� 
	void RunLoop(); // ������� ����
	void Shutdown(); // Close the app

private:
	// ��������������� ������� ��� �������� �����

	void ProcessInput();
	//void updategame(); // ���������� ���� 
	//void generateoutput();
	SDL_Window* mWindow; // �������� ����
	bool mIsRunning; // �������� ������� ����

};