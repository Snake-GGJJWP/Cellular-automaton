#include <iostream>
#include "StartButton.h"

const int FRAME_LIMIT = 30;

StartButton::StartButton(Window* win,
						 Field* destField,
						 SDL_Rect container,
						 char* pathToTexture,
						 char* pathToHover) : Button(win) {
	this->container = container;

	renderer = win->getRenderer();
	frameLimitter = win->getFrameLimitter();

	SDL_Surface* surface = SDL_LoadBMP(pathToTexture);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Surface* surfaceHover = SDL_LoadBMP(pathToHover);
	textureHover = SDL_CreateTextureFromSurface(renderer, surfaceHover);
	SDL_FreeSurface(surface);
	
	field = destField;
}

void StartButton::render() {
	if (isHovered) {
		SDL_RenderCopy(renderer, textureHover, NULL, &container);
	}
	else {
		SDL_RenderCopy(renderer, texture, NULL, &container);
	}
}

void StartButton::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && isHovered) {
		std::cout << "Button was clicked!" << std::endl;
		field->setField();
		field->switchRunning();

		// Heuristic
		frameLimitter->setFPS(frameLimitter->getFPS() == FRAME_LIMIT ? -1 : FRAME_LIMIT);
	}
	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorOnButton(event->motion.x, event->motion.y);
	}
}

bool StartButton::isCursorOnButton(int x, int y) {
	return (x > container.x &&
			x < container.x + container.w &&
			y > container.y &&
			y < container.y + container.h);
}