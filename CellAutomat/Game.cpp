#include <iostream>
#include <cmath>

#include "Game.h"

/*
* It's better to make scaleX and scaleY such that width and height are dividable by them
*/
Game::Game(const char* title, int xPos, int yPos, int width, int height, float scaleX, float scaleY, bool fullscreen, int n, int m, bool** field) {
	// Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialize..." << std::endl;
		return;
	}

	int flag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	// Window init
	window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);
	if (!window) {
		std::cout << "Failed to create a window..." << std::endl;
		return;
	}
	screenWidth = width;
	screenHeight = height;

	// Renderer init
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "Failed to create a renderer..." << std::endl;
		return;
	}
	SDL_RenderSetScale(renderer, scaleX, scaleY);
	scaledWidth = screenWidth / scaleX;
	scaledHeight = screenHeight / scaleY;


	isRunning = true;

	initAutomat(n, m, field);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	// std::cout << "[EVENT]: " << event.type << std::endl;

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		// Step-by-Step mode
		case SDL_KEYDOWN:
			// std::cout << SDL_GetKeyName(event.key.keysym.sym) << " " << event.key.keysym.scancode << std::endl;
			if (event.key.keysym.scancode == 79) {
				// automat->next();
			}
			break;

		default:
			break;
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	bool** field = automat->getField();
	for (int i = 0; i < automat->getHeight(); i++) {
		for (int j = 0; j < automat->getWidth(); j++) {
			if (field[i][j]) { SDL_RenderDrawPoint(renderer, j, i); }
		}
	}


	SDL_RenderPresent(renderer);
}

void Game::update() {
	frame++;
	automat->next();
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Quitted" << std::endl;
}

Game::~Game() {
	clean();
}

void Game::initAutomat(int n, int m, bool** field) {
	automat = new Automat(n, m, field);
}

void Game::initAutomat(int n, int m) {
	automat = new Automat(n, m);
}