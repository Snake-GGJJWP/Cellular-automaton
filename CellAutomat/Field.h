#pragma once
#include "Widget.h"
#include "AutomatonController.h"
#include "AutomatDTO.h"
#include <iostream>

class Field : public Widget
{
public:
	Field(Window* window, AutomatonController* automatonController, SDL_Rect container);
	void handleEvent(SDL_Event*) override;
	void render() override;
	void update() override;

	// change isRunning from False to True and vice-versa
	void switchRunning() { isRunning = !isRunning; }

	// pass Field.field to AutomatonService
	/*void setField();*/

	// set the "color" of the cells we add
	// by color I mean the type of a cell (alive, dead, killer, generations etc)
	void setDrawingColor(int code) { drawingColor = code; }
	
	void setAutomat(AutomatDTO*);
	AutomatDTO* getAutomat();

	// turn everything 0 (black);
	void clearField();

	bool running() { return isRunning;  }

private:

	//uint8_t** field;
	//int fieldHeight = 0;
	//int fieldWidth = 0;
	AutomatDTO* automat;

	int cellSize;

	int cellHovered = -1; // -1 - if nothing hovered; 0 - w*h - number of cell hovered
	bool isRunning = false;
	bool isHovered = false;
	bool isMouseButtonPressed = false;

	int drawingColor = 1; // this will be put to a cell we want to color

	Window* window;
	SDL_Renderer* renderer;
	AutomatonController* automatonController;
};
