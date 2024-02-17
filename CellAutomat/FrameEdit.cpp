#include "FrameEdit.h"

FrameEdit::FrameEdit(Window* win,
					 TTF_Font* font,
					 SDL_Rect cont,
					 SDL_Color textColor,
					 std::string* pathToTexture) :
	Edit(win, font, cont, textColor, pathToTexture),
	textColorOK(textColor)
{
	texture = loadTexture(pathToTexture->c_str());
}

void FrameEdit::setTextColorOK() {
	textColor = textColorOK;
}

void FrameEdit::setTextColorError() {
	textColor = textColorError;
}