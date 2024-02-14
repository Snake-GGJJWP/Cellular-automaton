#include <iostream>
#include "StartButton.h"

const int FPS_MAX = 120;
const int FPS_MIN = 5;


StartButton::StartButton(Window* win,
						 Field* destField,
						 SDL_Rect container,
						 char* pathToStartTexture,
						 char* pathToStartHover,
						 char* pathToStopTexture,
						 char* pathToStopHover) : Button(win) {
	this->container = container;

	renderer = win->getRenderer();
	frameLimitter = win->getFrameLimitter();

	textureStart = loadTexture(pathToStartTexture);
	textureStartHover = loadTexture(pathToStartHover);
	textureStop = loadTexture(pathToStopTexture);
	textureStopHover = loadTexture(pathToStopHover);

	field = destField;
}

void StartButton::render() {
	// using SDL_Texture*[4]
	// int hover = isHovered ? 1 : 0;
	// int run = field->running() ? 1 : 0;
	// arr[hover*2+run]; 

	if (isHovered) {
		if (field->running()) {
			SDL_RenderCopy(renderer, textureStopHover, NULL, &container);
		}
		else {
			SDL_RenderCopy(renderer, textureStartHover, NULL, &container);
		}
	}
	else {
		if (field->running()) {
			SDL_RenderCopy(renderer, textureStop, NULL, &container);
		}
		else {
			SDL_RenderCopy(renderer, textureStart, NULL, &container);
		}
	}
}

void StartButton::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && isHovered) {
		field->setField();

		int fps;
		std::string* fpsString = frameEdit->getText();

		// If we found incorrect symbol in text then
		// show it to user, keep the default FPS (MAX_FPS / 2)
		// else parse the text into int
		for (auto it = fpsString->begin(); it != fpsString->end(); ++it) {

			// if current symbol is not in allowed list then ...
			if (frameEdit->ALLOWED_SYMBOLS.find(*it) == frameEdit->ALLOWED_SYMBOLS.end()) {
				std::cout << "Wrong symbol\n";
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
										(char*)"ERROR",
										(char*)"Invalid fps...",
										window->getWindow());
				frameEdit->setTextColorError();
				return;
			}
		}

		fps = std::stoi(*fpsString);
		fps = fps > FPS_MAX ? FPS_MAX : fps;
		fps = fps < FPS_MIN && fps >= 0 ? FPS_MIN : fps; // if it's less than 0 we do it with max speed

		frameEdit->setTextColorOK();

		// If field runs then remove frame limit, else set frame limit to
		// given FPS or FPS_MAX if the former exceeds it
		frameLimitter->setFPS(field->running() ? -1 : fps);

		field->switchRunning();
	}
	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorOnButton(event->motion.x, event->motion.y);
	}
}

bool StartButton::isCursorOnButton(int x, int y) {
	return (x > container.x &&
			x < container.x + container.w &&
			y > container.y &&
			y < container.y + container.h);
}