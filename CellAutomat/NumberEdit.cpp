#include "NumberEdit.h"

// Extended Edit field which won't contain any symbols other than numbers, +, -
// Also can change color to emphasize errors
NumberEdit::NumberEdit(Window* win,
					 TTF_Font* font,
					 SDL_Rect cont,
					 SDL_Color textColor,
					 std::string pathToTexture) :
	Edit(win, font, cont, textColor, pathToTexture),
	textColorOK(textColor)
{
}

void NumberEdit::handleEvent(SDL_Event* event) {
	bool isClickCtrlV = event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL;
	if (isClickCtrlV) {
		std::string clip = SDL_GetClipboardText();
		for (auto it = clip.begin(); it != clip.end(); ++it) {
			// if current symbol is not in allowed list then ...
			if (ALLOWED_SYMBOLS.find(*it) == ALLOWED_SYMBOLS.end()) {
				std::cout << "Wrong symbol\n";
				return;
			}
		}
	}
	else if (event->type == SDL_TEXTINPUT && isFocused && ALLOWED_SYMBOLS.find(event->text.text[0]) == ALLOWED_SYMBOLS.end()) {
		std::cout << "Don't type that here!\n";
		return;
	}
	Edit::handleEvent(event);
}

void NumberEdit::setTextColorOK() {
	textColor = textColorOK;
	isRendered = false;
}

void NumberEdit::setTextColorError() {
	textColor = textColorError;
	isRendered = false;
}