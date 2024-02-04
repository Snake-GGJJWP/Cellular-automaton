#pragma once

#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "Widget.h"

class Edit : public Widget
{
public:
	Edit(Window* win, std::string* startString, std::string* ttfFile, int fontSize);

	// Maybe make a default function that would process all we need here?
	// And if we would want to change or add functionality we would overwrite it in a children class?
	virtual void handleEvent(SDL_Event* event);
	virtual void render() {};

protected:
	std::string* editString;
	TTF_Font* font;

private:
	void loadFont(std::string* ttfFile, int fontSize);
};
