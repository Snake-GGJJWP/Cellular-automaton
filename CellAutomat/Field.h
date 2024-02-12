#pragma once
#include "Widget.h"
#include "AutomatonController.h"
#include <iostream>

class Field : public Widget
{
public:
	Field(Window* window, AutomatonController* automaotnController, SDL_Rect container);
	void handleEvent(SDL_Event*) override;
	void render() override;
	void update() override;

	// change isRunning from False to True and vice-versa
	void switchRunning() { isRunning = !isRunning; }

	// pass Field.field to AutomatonService
	void setField();

	bool running() { return isRunning;  }
	void printName() override { std::cout << "I'm field\n"; }

private:
	bool isCursorOnField(int x, int y);

	bool** field;
	int fieldHeight;
	int fieldWidth;
	int cellSize;

	int cellHovered = -1; // -1 - if nothing hovered; 0 - w*h - number of cell hovered
	bool isRunning = false;
	bool isHovered = false;
	bool isMouseButtonPressed = false;

	SDL_Rect container;

	Window* window;
	SDL_Renderer* renderer;
	AutomatonController* automatonController;
};
