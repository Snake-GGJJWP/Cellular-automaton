#pragma once
#include "Edit.h"

class TextEdit : public Edit
{
public:
	TextEdit(Window* win,
			 TTF_Font* font,
			 SDL_Rect container,
			 SDL_Color textColor,
			 std::string* pathToTexture);

	void setTextColorError();
	void setTextColorOK();

private:

	SDL_Color textColorOK;
	SDL_Color textColorError{ 255,0,0,255 }; // red
};
