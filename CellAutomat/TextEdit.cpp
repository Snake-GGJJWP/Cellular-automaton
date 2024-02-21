#include "TextEdit.h"

TextEdit::TextEdit(Window* win,
				   TTF_Font* font,
				   SDL_Rect container,
				   SDL_Color textColor,
				   std::string* pathToTexture) :
	Edit(win, font, container, textColor, pathToTexture),
	textColorOK(textColor)
{

}

void TextEdit::setTextColorOK() {
	textColor = textColorOK;
}

void TextEdit::setTextColorError() {
	textColor = textColorError;
}