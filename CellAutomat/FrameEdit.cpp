#include <stdexcept>

#include "FrameEdit.h"

FrameEdit::FrameEdit(Window* win, 
					 SDL_Rect cont,
					 SDL_Color textColor,
					 std::string *ttfFile,
					 int fontSize,
					 std::string *pathToTexture,
					 std::string *startText = new std::string("OWO")) :
	Edit(win, startText, ttfFile, fontSize),
	container(cont),
	textColor(textColor),
	renderer(win->getRenderer())
{
	SDL_Surface* surface = SDL_LoadBMP(pathToTexture->c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void FrameEdit::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		focus = isHovered; // if hovered then focus, if unhovered then unfocus
		std::cout << "FrameEdit focus: " << (focus ? "ON" : "OFF") << "\n";
	}
	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorInField(event->motion.x, event->motion.y);
	}
	else {
		Edit::handleEvent(event); // let our parent do the rest
	}
}

void FrameEdit::render() {
	SDL_RenderCopy(renderer, texture, NULL, &container);
	renderText();
}

void FrameEdit::renderText() {
	SDL_Surface* surface;
	char onFocusChar = focus ? '|' : ' '; // maybe in some universe I made it blinking. But not in this one.
	surface = TTF_RenderText_Solid(font, (*editString+onFocusChar).c_str(), textColor);

	SDL_Rect textContainer{ container.x + 5, container.y + ((container.h - surface->h) / 2), surface->w, surface->h };
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textContainer);
	SDL_DestroyTexture(textTexture);
}

bool FrameEdit::isCursorInField(int x, int y) {
	return (x > container.x &&
			x < container.x + container.w &&
			y > container.y &&
			y < container.y + container.h);
}