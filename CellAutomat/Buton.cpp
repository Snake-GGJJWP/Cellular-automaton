#include "Button.h"

Button::Button(Window* win, SDL_Rect container) : 
	Widget(win, container),
	renderer(win->getRenderer())
{}

void Button::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && isHovered) {
		onClick();
	}
	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorOnWidget(event->motion.x, event->motion.y);
	}
}

void Button::render() {
	if (texture == NULL) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
		SDL_RenderFillRect(renderer, &container);
	}
	else {
		SDL_RenderCopy(renderer, texture, NULL, &container);
	}
}