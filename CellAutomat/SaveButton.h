#pragma once
#include "Button.h"

class SaveButton : public Button
{
public:
	SaveButton(Window* win, SDL_Rect cont, char* pathToTexture, char* pathToTextureHover);

private:
	void onClick();
};
