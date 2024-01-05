#include "Field.h"
#include "iostream"

void printMatField(bool** mat, int n, int m) {
	// system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << (mat[i][j] ? "1" : "0") << " ";
		}
		std::cout << "\n";
	}
}

Field::Field(Window* window, 
			AutomatonController* automatonController,
			SDL_Rect container) : Widget(window) {
	this->container = container;

	this->automatonController = automatonController;
	fieldHeight = automatonController->getHeight();
	fieldWidth = automatonController->getWidth();
	renderer = window->getRenderer();

	field = automatonController->getNextIteration();
	// printMatField(field, fieldHeight, fieldWidth);
}

void Field::handleEvent(SDL_Event* event) {
}

void Field::render() {
	if (!isRunning) {
		return;
	}

	SDL_SetRenderDrawColor(renderer, 225, 146, 67, 255);
	SDL_RenderDrawRect(renderer, &container);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &container);
	SDL_SetRenderDrawColor(renderer, 225, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, container.x + 8, container.y + 8);

	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			if (field[i][j]) { SDL_RenderDrawPoint(renderer, j+container.x, i+container.y); }
		}
	}
	
}

void Field::update() {
	if (!isRunning) {
		return;
	}

	field = automatonController->getNextIteration();
}