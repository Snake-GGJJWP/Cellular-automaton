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
	textColorCurrent(textColor),
	textColorOK(textColor),
	renderer(win->getRenderer())
{
	SDL_Surface* surface = SDL_LoadBMP(pathToTexture->c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

FrameEdit::FrameEdit(Window* win,
					 SDL_Rect cont,
					 SDL_Color textColor,
					 TTF_Font* font,
					 std::string* pathToTexture,
					 std::string* startText = new std::string("OWO")) :
	Edit(win, startText, font),
	container(cont),
	textColorCurrent(textColor),
	textColorOK(textColor),
	renderer(win->getRenderer())
{
	SDL_Surface* surface = SDL_LoadBMP(pathToTexture->c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}



void FrameEdit::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		isFocused = isHovered; // if hovered then focus, if unhovered then unfocus
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
	if (textTexture != nullptr) {
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}
	char onFocusChar = isFocused ? '|' : ' '; // maybe in some universe I made it blinking. But not in this one.
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, (*editString + onFocusChar).c_str(), textColorCurrent);

	SDL_Rect textContainer{ container.x + 5, container.y + ((container.h - surface->h) / 2), surface->w, surface->h };

	textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textContainer);
}

bool FrameEdit::isCursorInField(int x, int y) {
	return (x > container.x &&
			x < container.x + container.w &&
			y > container.y &&
			y < container.y + container.h);
}