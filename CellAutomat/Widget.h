#pragma once
#include "Window.h"
#include "SDL_image.h"

// Maybe make several different interfaces like EventHandler, Renderable, Updatable?

// Interface
class Widget
{
public:
	Widget(Window* win, SDL_Rect container) : window(win), container(container) {}
	
	virtual void handleEvent(SDL_Event* event) { }
	virtual void render() {}

	virtual void update() {}

	virtual void printName() {
	}

protected:
	virtual SDL_Texture* loadTexture(const char* pathToTexture) {
		SDL_Texture* texture = IMG_LoadTexture(window->getRenderer(), pathToTexture);
		if (texture == NULL) {
			std::cout << "Error during texture loading\n" << IMG_GetError() << "\n";
		}
		return texture;
	};

	virtual bool isCursorOnWidget(int x, int y) {
		return (x > container.x &&
				x < container.x + container.w &&
				y > container.y &&
				y < container.y + container.h);
	}

	Window* window;
	SDL_Rect container;
};
