#include <Game.h>
#include <iostream>
#include <SDL.h>


Game::Game(const char* title, int xPos, int yPos, int width, int heigth, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to run..." << endl;

		return;
	}

	window SDL_Create
}