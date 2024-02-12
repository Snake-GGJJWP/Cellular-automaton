#pragma once

#include <SDL_ttf.h>
#include <string>

#include "Widget.h"

class Label : public Widget
{
public:
	Label(Window* win, 
		  SDL_Rect container,
		  SDL_Color textColor,
		  std::string pathToTTF, 
		  int fontSize, 
		  std::string text);

	Label(Window* win,
		  SDL_Rect container,
		  SDL_Color textColor,
		  TTF_Font* font, 
		  std::string text);

	void render() override;

	void setColor(SDL_Color color) { textColor = color; }
	void setText(std::string text) { this->text = text; }


private:
	void loadFont(std::string& ttfFile, int fontSize);

	std::string text;
	SDL_Color textColor;
	TTF_Font* font;
	SDL_Rect container;
	SDL_Texture* textTexture;
	SDL_Renderer* renderer;
};
