#pragma once
#include "Button.h"
#include "Field.h"
#include "vector"

// It can be created only by ColorPalette
// I wonder if we actually need it...
// PROBLEM:  In some cases we must create too many widgets which will handle events
// SOLUTION: Remove this class and make ColorPalette's handleEvent() calculate
//			 which color user picked
// This is my TODO here
class ColorButton : public Button
{
public:
	void handleEvent(SDL_Event* event) override;
	void render() override;

	friend class ColorPalette;

private:
	ColorButton(Window* win, Field* field, SDL_Rect container, SDL_Color color, int code);

	bool isCursorOnButton(int x, int y) override;
	
	bool isHovered = false;

	int code;
	SDL_Color color;
	SDL_Rect container;
	Field* field;

	SDL_Renderer* renderer;
};


class ColorPalette : public Widget
{
public:
	ColorPalette(Window* win, 
				 Field* field, 
				 SDL_Rect container, 
				 std::vector<SDL_Color> colors,
				 int buttonSize);

	void render() override;
	void handleEvent(SDL_Event* event) override;

	void setColors(std::vector<SDL_Color> colors);
	void addColor(SDL_Color color);

private:
	std::vector<Button*> colorButtons;
	
	unsigned int buttonSize;
	SDL_Rect container;
	Field* field;

	SDL_Renderer* renderer;
};

