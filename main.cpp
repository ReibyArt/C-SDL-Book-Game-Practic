﻿#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "Game.h"
using namespace std;


int main(int argc, char* args[]) {
	
	Game game;

	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	game.Shutdown();

	/*cout << "Hello!" << endl;*/
	return 0;
}