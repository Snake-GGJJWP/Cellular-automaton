#include "SetButton.h"
#include "AutomatMapper.h"

const uint16_t MAX_WIDTH = 600;
const uint16_t MIN_WIDTH = 1;
const uint16_t MAX_HEIGHT = 600;
const uint16_t MIN_HEIGHT = 1;


void printMat3(uint8_t** mat, int n, int m) {
	// system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << (mat[i][j] ? "1" : "0") << " ";
		}
		std::cout << std::endl;
	}
}

SetButton::SetButton(Window* win,
					 Field* field,
					 NumberEdit* widthEdit,
					 NumberEdit* heightEdit,
					 TextEdit* ruleEdit,
					 ColorPalette* colorPalette,
					 SDL_Rect container,
					 char* pathToTexture,
					 char* pathToTextureHover) :
	Button(win, container),
	field(field),
	widthEdit(widthEdit),
	heightEdit(heightEdit),
	ruleEdit(ruleEdit),
	colorPalette(colorPalette)
{
	setTexture(pathToTexture);
	setTextureHover(pathToTextureHover);
}

void SetButton::onClick() {
	if (field->running()) {
		return;
	}

	AutomatDTO* automat = field->getAutomat();

	// Getting info from edits
	int newWidth = std::stoi(widthEdit->getText());
	int newHeight = std::stoi(heightEdit->getText());
	std::string rule = ruleEdit->getText();

	// Width and Height validation
	bool isWidthInvalid = newWidth > MAX_WIDTH || newWidth < MIN_WIDTH;
	if (isWidthInvalid) {
		std::cout << "Invalid width!\n";
		widthEdit->setTextColorError();
		giveError("Invalid width! Width must be in range of [1, 600]");
		return;
	}
	widthEdit->setTextColorOK();

	bool isHeightInvalid = newHeight > MAX_WIDTH || newHeight < MIN_WIDTH;
	if (isHeightInvalid) {
		std::cout << "Invalid height!\n";
		heightEdit->setTextColorError();
		giveError("Invalid height! Width must be in range of [1, 600]");
		return;
	}
	heightEdit->setTextColorOK();

	// Setting new rule
	// I use a method from the mapper because it fits so well here
	// But in theory if 2 different people were working on back and front
	// They would have 2 different methods to parse the rule (which would be private of course)
	// But I'm the only one working here so who cares ¯\_(ツ)_/¯
	std::string newRule = ruleEdit->getText();
	if (!AutomatMapper::parseRule(newRule, automat)) {
		ruleEdit->setTextColorError();
		giveError("Incorrect rule!\n"); // maybe make a method in mapper that would give back the error?
		return;
	}
	ruleEdit->setTextColorOK();

	// Creating new field: 
	// if new field is smaller - crop old one and fit it in the new one,
	// otherwise - fill spaces with 0
	uint8_t** newField = new uint8_t*[newHeight];
	for (int i = 0; i < newHeight; i++) {
		newField[i] = new uint8_t[newWidth];

		for (int j = 0; j < newWidth; j++) {
			bool isCoordInOldField = j < automat->width && i < automat->height;
			newField[i][j] = (isCoordInOldField) ? min(automat->field[i][j], automat->generations - 1) : 0;
		}
	}

	automat->width = newWidth;
	automat->height = newHeight;
	automat->rule = newRule;
	automat->field = newField;

	field->setAutomat(automat);
	colorPalette->setColors(field->getColors());
}

void SetButton::giveError(std::string text) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
							 (char*)"INPUT ERROR",
							 text.c_str(),
							 window->getWindow());
}

uint8_t SetButton::min(uint8_t a, uint8_t b) {
	return a < b ? a : b;
}