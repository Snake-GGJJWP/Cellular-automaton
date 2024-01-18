#pragma once
#include "Widget.h"

class Button : public Widget
{
public:
	Button(Window* win) : Widget(win) {}
	virtual void handleEvent(SDL_Event* event) { }
	virtual void render() {};
private:
	virtual bool isCursorOnButton(int x, int y) { return false; }
};