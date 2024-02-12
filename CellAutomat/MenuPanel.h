#pragma once

#include "Widget.h"
#include <iostream>

/*
* Some random idea:
* Make a Layout interface which would store and postion assigned components relatively.
* - SDL_Rect container {x, y, w, h}
* - int maxColumn = 1;
* - int maxRow = 1;
* - std::vector<Widgets> widgets;
* - void addComponent(Widget component, row, column) { vector.push_back({component, row, column}); }
* - void render() {
*		for (widget : widgets) {
*			...find out startPosition from row and column
*			...render widget
*		}
* }
* 
* Problem: added components must be resizable, or else it will be a messy shit.
*/


class MenuPanel: public Widget
{
public:
	MenuPanel(Window* win, SDL_Rect container, char* pathToTexture);
	void render() override;

	void printName() override {
		std::cout << "I'm MenuPanel!\n";
	}
private:
	SDL_Rect container;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};
