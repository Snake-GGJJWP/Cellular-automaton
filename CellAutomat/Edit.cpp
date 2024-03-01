#include "Edit.h"

Edit::Edit(Window* win, 
		   std::string ttfFile, 
		   int fontSize,
		   SDL_Rect cont,
		   SDL_Color textColor,
		   std::string pathToTexture) :
	Widget(win, cont),
	textColor(textColor),
	renderer(win->getRenderer())
{
	loadFont(ttfFile, fontSize);
	texture = loadTexture(pathToTexture.c_str());

	int w, h;
	TTF_SizeText(font, "|", &w, &h);
	cursorWidth = w;
}

Edit::Edit(Window* win, 
		   TTF_Font* font, 
		   SDL_Rect cont,
		   SDL_Color textColor,
		   std::string pathToTexture) :
	Widget(win, cont),
	font(font),
	textColor(textColor),
	renderer(win->getRenderer())
{
	texture = loadTexture(pathToTexture.c_str());
	int w, h;
	TTF_SizeText(font, "|", &w, &h);
	cursorWidth = w;
}



void Edit::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		isFocused = isHovered; // if hovered then focus, if unhovered then unfocus
	}

	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorOnWidget(event->motion.x, event->motion.y);
	}

	if (!isFocused) return;

	switch (event->type) {

	//Special key input
	case SDL_KEYDOWN:
		//BACKSPACE
		if (event->key.keysym.sym == SDLK_BACKSPACE && editString.length() > 0 && indToPlace > 0)
		{
			// Getting size of symbol we deleted
			int w, h;
			TTF_SizeText(font, editString.substr(indToPlace-1, 1).c_str(), &w, &h);

			std::cout << w << "\n";

			editString.erase(indToPlace - 1, 1);
			indToPlace--;
			startX = (startX - w) <= 0 ? 0 : startX - w; // move cutting pointer to sym width to left
		}

		//COPY
		else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(editString.c_str());
		}

		//PASTE
		else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			editString = SDL_GetClipboardText();
			if (stringLimit >= 0 && editString.length() > charLimit) {
				editString.erase(charLimit, editString.length() - charLimit);
			}
			indToPlace = editString.length();
			int cW = cursorX();
			startX = cW > (startX + container.w - TEXT_MARGIN) ? cW - (container.w - TEXT_MARGIN) : startX;
		}

		//MOVE CURSOR LEFT
		else if (event->key.keysym.sym == SDLK_LEFT) {
			indToPlace -= indToPlace <= 0 ? 0 : 1; // don't substract if it's already 0

			// Check if cursor is out of rendered text
			// If it is then move starting rendering point to cursor
			int cW = cursorX();
			startX = cW < startX ? cW - cursorWidth : startX;
		}

		//MOVE CURSOR RIGHT
		else if (event->key.keysym.sym == SDLK_RIGHT) {
			indToPlace += indToPlace >= editString.length() ? 0 : 1; // don't increment if it's already reached the end

			// Check if cursor is out of field
			// If it is then move starting rendering point to cursor
			int cW = cursorX();
			startX = cW > (startX + container.w - TEXT_MARGIN) ? cW - (container.w - TEXT_MARGIN) : startX;
		}

		break;

		//Special text input event
	case SDL_TEXTINPUT:
		// Not copy or pasting and 
		// editString is within range (if charLimit = -1 do not check)
		if (!(SDL_GetModState() & KMOD_CTRL &&
			(event->text.text[0] == 'c' || event->text.text[0] == 'C' ||
				event->text.text[0] == 'v' || event->text.text[0] == 'V')) &&
			(charLimit < 0 || editString.length() < charLimit))
		{
			//Append character
			editString.insert(indToPlace, 1, event->text.text[0]);
			indToPlace++;

			// Check if cursor is out of field
			// If it is then move starting rendering point to cursor
			int cW = cursorX();
			startX = cW > (startX + container.w - TEXT_MARGIN) ? cW - (container.w - TEXT_MARGIN) : startX;
		}
		break;
	}
}

void Edit::render() {
	SDL_RenderCopy(renderer, texture, NULL, &container);
	renderText();
}

void Edit::renderText() {
	// Delete current texture;
	if (textTexture != nullptr) {
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}

	std::string renderString;
	renderString = editString;

	// Add cursor if needed
	if (isFocused) {
		renderString.insert(indToPlace - (editString.length() - renderString.length()), "|");
	}

	// Create texture if there's something to render...
	if (renderString.length() != 0) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, renderString.c_str(), textColor);

		SDL_Rect textContainer{ container.x + TEXT_MARGIN, 
								container.y + ((container.h - surface->h) / 2), 
								surface->w > (container.w - TEXT_MARGIN) ? (container.w - TEXT_MARGIN) : surface->w,
								surface->h > container.h ? container.h : surface->h };

		SDL_Rect cropContainer{ surface->w > (container.w - TEXT_MARGIN) ? startX : 0,
								0, 
								surface->w > (container.w - TEXT_MARGIN) ? (container.w - TEXT_MARGIN) : surface->w,
								surface->h > container.h ? container.h : surface->h };

		textTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		SDL_RenderCopy(renderer, textTexture, &cropContainer, &textContainer);
	}
}

void Edit::loadFont(std::string ttfFile, int fontSize) {
	font = TTF_OpenFont(ttfFile.c_str(), fontSize);
	if (font == NULL) {
		std::cout << "FAILED TO LOAD THE FONT\n";
		std::cout << TTF_GetError();
		throw std::invalid_argument("path to .ttf file is unreachable");
	}
}

void Edit::setText(std::string str) {
	editString = str;
	indToPlace = editString.length();
};

void Edit::setCharLimit(int limit) {
	charLimit = limit;
}

int Edit::cursorX() {
	int w, h;
	TTF_SizeText(font, (editString.substr(0, indToPlace)+"|").c_str(), &w, &h);
	return w;
}