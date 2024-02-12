#pragma once
#include "Window.h"

// Maybe make several different interfaces like EventHandler, Renderable, Updatable?

// Interface
class Widget
{
public:
	Widget(Window* win) : window(win)  {}
	
	virtual void handleEvent(SDL_Event* event) { }
	virtual void render() {}

	virtual void update() {}

	virtual void printName() {
	}

protected:
	Window* window;
};
