#include "MenuPanel.h"

MenuPanel::MenuPanel(Window* window, SDL_Rect container, char* pathToTexture) : Widget(window) {
	this->container = container;
	this->renderer = window->getRenderer();

	SDL_Surface* surface = SDL_LoadBMP(pathToTexture);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void MenuPanel::render() {
	SDL_RenderCopy(renderer, texture, NULL, &container);
}