#include <iostream>
#include "StartButton.h"

StartButton::StartButton(Window* win,
						 Field* destField,
						 SDL_Rect container,
						 char* pathToTexture) : Button(win) {
	this->container = container;

	renderer = win->getRenderer();

	SDL_Surface* surface = SDL_LoadBMP(pathToTexture);
	buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	field = destField;
}

void StartButton::render() {
	SDL_RenderCopy(renderer, buttonTexture, NULL, &container);

}

void StartButton::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && isHovered) {
		std::cout << "Button was clicked!" << std::endl;
		field->setField();
		field->switchRunning();
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