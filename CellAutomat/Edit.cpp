#include "Edit.h"

Edit::Edit(Window* win, std::string* startString, std::string* ttfFile, int fontSize) : 	
	Widget(win),
	editString(startString)
{
	loadFont(ttfFile, fontSize);
}

void Edit::loadFont(std::string* ttfFile, int fontSize) {
	font = TTF_OpenFont(ttfFile->c_str(), fontSize);
	if (font == NULL) {
		std::cout << "FAILED TO LOAD THE FONT\n";
		std::cout << TTF_GetError();
		throw std::invalid_argument("path to .ttf file is unreachable");
	}
}

void Edit::handleEvent(SDL_Event* event) {
	//Special key input
	if (event->type == SDL_KEYDOWN) {

		//BACKSPACE
		if (event->key.keysym.sym == SDLK_BACKSPACE && editString->length() > 0)
		{
			editString->pop_back();
		}

		//COPY
		else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(editString->c_str());
		}

		//PASTE
		else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			*editString = SDL_GetClipboardText();
		}
	}

	//Special text input event
	else if (event->type == SDL_TEXTINPUT)
	{
		//Not copy or pasting
		if (!(SDL_GetModState() & KMOD_CTRL && (event->text.text[0] == 'c' || event->text.text[0] == 'C' || event->text.text[0] == 'v' || event->text.text[0] == 'V')))
		{
			//Append character
			*editString += event->text.text;
		}
	}
}