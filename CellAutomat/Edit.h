#pragma once

#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "Widget.h"

const int TEXT_MARGIN = 5;

class Edit : public Widget
{
public:
	Edit(Window* win, std::string* ttfFile, int fontSize, SDL_Rect cont, SDL_Color textColor, std::string* pathToTexture);
	Edit(Window* win, TTF_Font* font, SDL_Rect cont, SDL_Color textColor, std::string* pathToTexture);

	virtual void handleEvent(SDL_Event* event);
	virtual void render();
	virtual std::string* getText() { return editString; };
	virtual void setText(std::string* str);
	virtual void setCharLimit(int limit);
	

protected:
	virtual void renderText();

	bool isFocused = false;
	bool isHovered = false;

	std::string* editString = new std::string("");
	int indToPlace = 0;
	int charLimit = -1; // how much charachters string can contain
	int stringLimit = -1; // how mich charachtes edit can show

	TTF_Font* font;
	SDL_Color textColor;
	SDL_Texture* texture = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Renderer* renderer;

private:
	void loadFont(std::string* ttfFile, int fontSize);
	int cursorX(); // get x coord where cursor is currently in
	int startX = 0; // string cutting starting x coordinate
	int cursorWidth; // width of cursor charachter;
};
