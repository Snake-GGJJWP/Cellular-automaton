#include "MenuPanel.h"

MenuPanel::MenuPanel(Window* window, SDL_Rect container, char* pathToTexture) : Widget(window, container) {
	this->renderer = window->getRenderer();

	texture = loadTexture(pathToTexture);
}

void MenuPanel::render() {
	SDL_RenderCopy(renderer, texture, NULL, &container);
}