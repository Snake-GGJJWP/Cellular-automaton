#include <iostream>

#include "Label.h"

Label::Label(Window* win,
			 SDL_Rect container,
			 SDL_Color textColor,
			 std::string pathToTTF,
			 int fontSize,
			 std::string text) :
	Widget(win, container),
	textColor(textColor),
	text(text),
	renderer(win->getRenderer())
{
	loadFont(pathToTTF, fontSize);
}

Label::Label(Window* win,
			 SDL_Rect container,
			 SDL_Color textColor,
			 TTF_Font* font,
			 std::string text) :
	Widget(win, container),
	textColor(textColor),
	text(text),
	font(font),
	renderer(win->getRenderer())
{
}

void Label::render() {
	if (textTexture != nullptr) {
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	SDL_Rect textContainer{ container.x + 5, container.y + ((container.h - surface->h) / 2), surface->w, surface->h };

	textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textContainer);
}

void Label::loadFont(std::string& ttfFile, int fontSize) {
	font = TTF_OpenFont(ttfFile.c_str(), fontSize);
	if (font == NULL) {
		std::cout << "FAILED TO LOAD THE FONT\n";
		std::cout << TTF_GetError();
		throw std::invalid_argument("path to .ttf file is unreachable");
	}
}