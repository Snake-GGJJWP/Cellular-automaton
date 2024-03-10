#include "Button.h"

Button::Button(Window* win, SDL_Rect container) : 
	Widget(win, container),
	renderer(win->getRenderer())
{}

void Button::handleEvent(SDL_Event* event) {
	bool buttonClicked = event->type == SDL_MOUSEBUTTONDOWN;
	bool mouseMotion = event->type == SDL_MOUSEMOTION;

	if (buttonClicked && isHovered) {
		onClick();
		isRendered = false;
	}
	else if (mouseMotion) {
		isHovered = isCursorOnWidget(event->motion.x, event->motion.y);
		isRendered = false;
	}
}

void Button::render() {
	// Problem: Spaghetti
	if (isHovered) {
		if (textureHover != NULL) {
			SDL_RenderCopy(renderer, textureHover, NULL, &container);
		}
		else if (texture != NULL) {
			SDL_RenderCopy(renderer, texture, NULL, &container);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
			SDL_RenderFillRect(renderer, &container);
		}
	}
	else {
		if (texture != NULL) {
			SDL_RenderCopy(renderer, texture, NULL, &container);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
			SDL_RenderFillRect(renderer, &container);
		}
	}
}