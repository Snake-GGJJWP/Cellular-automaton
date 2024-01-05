#pragma once
#include "Button.h"
#include "Field.h"

class StartButton : public Button
{
public:
	StartButton(Window* win, Field* destField, SDL_Rect container, char* pathToTexture);
	void handleEvent(SDL_Event*) override;
	void render() override;
private:
	bool isCursorOnButton(int, int) override;

	bool isHovered = false;

	Field* field;

	SDL_Rect container;
	SDL_Texture* buttonTexture = nullptr;
	SDL_Renderer* renderer;
};