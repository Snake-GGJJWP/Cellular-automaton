#include <iostream>
#include "ColorPalette.h"

ColorPalette::ColorPalette(Window* win, 
						   Field* field,
						   SDL_Rect container,
						   std::vector<SDL_Color> colors,
						   int buttonSize) :
	Widget(win),
	field(field),
	container(container),
	buttonSize(buttonSize),
	renderer(win->getRenderer())
{
	setColors(colors);
}


/*
* Idea:
* For each color in the vector we create a button
* Each button has to change drawing color on click
* Button class will be created in ColorPalette class file (?)
* because we don't need it anywhere else
* 
*/
void ColorPalette::setColors(std::vector<SDL_Color> colors) {
	colorButtons.clear();
	for (auto color : colors) {
		static int i = 0;
		static int j = 0;
		static int code = 0;
		SDL_Rect cont = { container.x + buttonSize * i++,
						  container.y + buttonSize * j,
						  buttonSize,
						  buttonSize };

		if (i >= container.w / buttonSize) {
			i = 0;
			j++;
		}

		colorButtons.push_back(new ColorButton(window, field, cont, color, code++));
	}
}

void ColorPalette::render() {
	for (auto button : colorButtons) {
		button->render();
	}
}

void ColorPalette::handleEvent(SDL_Event* event) {
	for (auto button : colorButtons) {
		button->handleEvent(event);
	}
}

void ColorPalette::addColor(SDL_Color) {

}


// ## COLOR BUTTON METHODS ##

ColorButton::ColorButton(Window* win, Field* field, SDL_Rect container, SDL_Color color, int code) :
	Button(win),
	code(code),
	container(container),
	color(color),
	field(field),
	renderer(win->getRenderer())
{
}


void ColorButton::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && isHovered) {
		field->setDrawingColor(code);
		std::cout << "CLICKED! CODE: " << code << "\n";
	}
	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorOnButton(event->motion.x, event->motion.y);
	}
}

void ColorButton::render() {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &container);
}

bool ColorButton::isCursorOnButton(int x, int y) {
	return (x > container.x &&
			x < container.x + container.w &&
			y > container.y &&
			y < container.y + container.h);
}