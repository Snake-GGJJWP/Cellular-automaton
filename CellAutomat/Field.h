#pragma once
#include "Widget.h"
#include "AutomatonController.h"
#include "AutomatDTO.h"
#include <iostream>
#include <vector>

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

	std::vector<SDL_Color> getColors() { return colors; }

private:

	void setColorsForGenerations();
	SDL_Color HSBtoRGB(int h, double s, double b);

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

	// Colors of cell states
	// Only black and white at first
	std::vector<SDL_Color> colors = { SDL_Color{0,0,0,255},
									  SDL_Color{255,255,255,255} };

	Window* window;
	SDL_Renderer* renderer;
	AutomatonController* automatonController;
};
