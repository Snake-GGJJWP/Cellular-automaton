#include "MenuPanel.h"

MenuPanel::MenuPanel(Window* window, SDL_Rect container, SDL_Color fillingColor) : Widget(window) {
	this->container = container;
	this->fillingColor = fillingColor;
	this->renderer = window->getRenderer();
}

void MenuPanel::render() {
	SDL_SetRenderDrawColor(renderer, fillingColor.r, fillingColor.g, fillingColor.b, fillingColor.a);
	SDL_RenderDrawRect(renderer, &container);
	SDL_RenderFillRect(renderer, &container);
}