#pragma once
#include "Widget.h"

class Button : public Widget
{
public:
	Button(Window* win, SDL_Rect container);
	virtual void handleEvent(SDL_Event* event);
	virtual void render();

protected:
	void setTexture(char* pathToTexture) {
		texture = loadTexture(pathToTexture);
	}

	void setTextureHover(char* pathToTexture) {
		textureHover = loadTexture(pathToTexture);
	}

	virtual void onClick() {}

	bool isHovered = false;
	SDL_Renderer* renderer;

	SDL_Texture* texture = NULL;
	SDL_Texture* textureHover = NULL;
};