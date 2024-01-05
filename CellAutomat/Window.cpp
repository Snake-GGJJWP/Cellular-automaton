#include <iostream>
#include <cmath>

#include "Window.h"

/*
* NOT RESIZABLE (maybe add it later)
* It's better to make scaleX and scaleY such that width and height are dividable by them
*/
Window::Window(const char* title, int xPos, int yPos, int width, int height, float scaleX, float scaleY, bool fullscreen) {
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

	// render();


	isRunning = true;
}

void Window::handleEvent(const SDL_Event* event) {
	// std::cout << "[EVENT]: " << event.type << std::endl;

	switch (event->type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		// Step-by-Step mode
		case SDL_KEYDOWN:
			// std::cout << SDL_GetKeyName(event.key.keysym.sym) << " " << event.key.keysym.scancode << std::endl;
			if (event->key.keysym.scancode == 79) {
				// automat->next();
			}
			break;

		default:
			break;
	}
}

void Window::render() {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	/*bool** field = automat->getField();
	for (int i = 0; i < automat->getHeight(); i++) {
		for (int j = 0; j < automat->getWidth(); j++) {
			if (field[i][j]) { SDL_RenderDrawPoint(renderer, j, i); }
		}
	}*/
}

void Window::cleanRender() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Window::presentRender() {
	SDL_RenderPresent(renderer);
}

void Window::update() {
	frame++;
}

void Window::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Quitted" << std::endl;
}

Window::~Window() {
	clean();
}