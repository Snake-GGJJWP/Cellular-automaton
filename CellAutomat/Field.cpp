#include "Field.h"
#include "iostream"

const uint16_t DEFAULT_WIDTH = 50;
const uint16_t DEFAULT_HEIGHT = 50;

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
			SDL_Rect container) : 
	Widget(window, container),
	automatonController(automatonController),
	renderer(window->getRenderer())
{
	// move it somewhere else later
	automat = new AutomatDTO();
	automat->height = DEFAULT_HEIGHT;
	automat->width = DEFAULT_WIDTH;
	automat->rule = "B3/S23";
	automat->birth = { 3 };
	automat->survive = { 2,3 };

	// default field
	automat->field = new uint8_t * [automat->height];
	for (int i = 0; i < automat->height; i++) {
		automat->field[i] = new uint8_t[automat->width];
		for (int j = 0; j < automat->width; j++) {
			automat->field[i][j] = 0;
		}
	}

	cellSize = (automat->height > automat->width) ? container.h / automat->height : container.w / automat->width;
}

void Field::handleEvent(SDL_Event* event) {
	if (event->type == SDL_MOUSEBUTTONDOWN && isHovered && event->button.button == SDL_BUTTON_LEFT && !isRunning) {
		std::cout << "Field clicked!\n";

		isMouseButtonPressed = true;

		int fieldX = (event->button.x - container.x) / cellSize;
		int fieldY = (event->button.y - container.y) / cellSize;

		std::cout << "Calculated coord: (" << fieldX << ", " << fieldY << ")\n";
		
		// Checking just in case
		if (fieldX >= automat->width || fieldY >= automat->height) {
			std::cout << "Out of field!\n";
			std::cout << "Mouse coord: (" << event->button.x << ", " << event->button.y << ")\n";
			std::cout << "Field's size: " << automat->width << " " << automat->height << "\n";
			return;
		}
		automat->field[fieldY][fieldX] = drawingColor;
	}
	else if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		std::cout << "Released left button!\n";
		isMouseButtonPressed = false;
	}
	else if (event->type == SDL_MOUSEMOTION) {
		isHovered = isCursorOnWidget(event->motion.x, event->motion.y);

		if (isHovered && !isRunning) {
			int fieldX = (event->button.x - container.x) / cellSize;
			int fieldY = (event->button.y - container.y) / cellSize;

			if (fieldX >= automat->width || fieldY >= automat->height) {
				cellHovered = -1;
				return;
			}

			cellHovered = fieldY * automat->width + fieldX;
		}
		else {
			cellHovered = -1;
		}

		if (isMouseButtonPressed && !isRunning && isHovered) {
			automat->field[cellHovered / automat->width][cellHovered % automat->width] = drawingColor;
		}
	}
}

void Field::render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &container);
	SDL_SetRenderDrawColor(renderer, 225, 255, 255, 255);

	// Draw cells
	for (int i = 0; i < automat->height; i++) {
		for (int j = 0; j < automat->width; j++) {
			if (automat->field[i][j]) {
				SDL_Rect cell = { (container.x + j) * cellSize, (container.y + i) * cellSize, cellSize, cellSize };
				SDL_RenderFillRect(renderer, &cell);
			}
		}
	}
	
	// Draw hover rectangle
	if (!isRunning && cellHovered > -1) {
		SDL_Rect hoverRect = { container.x + (cellHovered % automat->width) * cellSize,
							   container.y + ((int)(cellHovered / automat->width)) * cellSize,
							   cellSize,
							   cellSize};
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // make opacity work
		SDL_SetRenderDrawColor(renderer, 180, 20, 0, 127); // half transparent dark red rect
		SDL_RenderFillRect(renderer, &hoverRect);
	}
}

void Field::update() {
	if (!isRunning) {
		return;
	}

	automatonController->nextIteration(automat);
}

//void Field::setField() {
//	automatonController->setHeight(automat.height);
//	automatonController->setWidth(automat.width);
//	automatonController->setField(automat.field);
//}

void Field::setAutomat(AutomatDTO* newAutomat) {
	if (newAutomat == NULL) {
		std::cout << "Can't set a NULL\n";
		return;
	}
	delete automat;
	automat = newAutomat;

	cellSize = (automat->height > automat->width) ? container.h / automat->height : container.w / automat->width;
}

AutomatDTO* Field::getAutomat() {
	return automat;
}

void Field::clearField() {
	for (int i = 0; i < automat->height; i++) {
		for (int j = 0; j < automat->width; j++) {
			automat->field[i][j] = 0;
		}
	}
}