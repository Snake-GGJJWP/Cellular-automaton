#pragma once
#include "Widget.h"
#include "AutomatonController.h"

class Field : public Widget
{
public:
	Field(Window* window, AutomatonController* automaotnController, SDL_Rect container);
	void handleEvent(SDL_Event*) override;
	void render() override;
	void update() override;

	// change isRunning from False to True and vice-versa
	void switchRunning() { isRunning = !isRunning; }

private:
	bool** field;
	int fieldHeight;
	int fieldWidth;
	int cellSize;
	bool isRunning = false;

	SDL_Rect container;

	Window* window;
	SDL_Renderer* renderer;
	AutomatonController* automatonController;
};
