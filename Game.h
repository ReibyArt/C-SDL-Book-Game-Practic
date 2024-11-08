#pragma once
#include <SDL.h>


// �������� ��������� ��� ���� � �������
struct Vector2
{
	float x;
	float y;
};

// ������� ������� �����
class Game 
{
public:

	Game();
	bool Initialize(); // ������������� 
	void RunLoop(); // ������� ����
	void Shutdown(); // Close the app

private:
	// ��������������� ������� ��� �������� �����
	void ProcessInput();
	void UpdateGame();
	

	void GenerateOutput();


	SDL_Window* mWindow; // �������� ����
	SDL_Renderer* mRenderer; // �������� �������
	bool mIsRunning; // �������� ������� ����

	// ������� ���� � �������
	Vector2 mBallPos;
	Vector2 mPaddlePos;
	float mPaddleDir = 0.0f;
	Vector2 mBallVel; 
	
	
};