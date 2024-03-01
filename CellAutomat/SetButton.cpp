#include "SetButton.h"
#include "AutomatMapper.h"

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
					 SDL_Rect container,
					 char* pathToTexture,
					 char* pathToTextureHover) :
	Button(win, container),
	field(field),
	widthEdit(widthEdit),
	heightEdit(heightEdit),
	ruleEdit(ruleEdit)
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

	// Creating new field: 
	// if new field is smaller - crop old one and fit it in the new one,
	// otherwise - fill spaces with 0
	uint8_t** newField = new uint8_t*[newHeight];
	for (int i = 0; i < newHeight; i++) {
		newField[i] = new uint8_t[newWidth];

		for (int j = 0; j < newWidth; j++) {
			newField[i][j] = (j < automat->width && i < automat->height) ? automat->field[i][j] : 0;
		}
	}

	// Setting new rule
	// I use a method from the mapper because it fits so well here
	// But in theory if 2 different people were working on back and front
	// They would have 2 different methods to parse the rule (which would be private of course)
	// But I'm the only one working here so who cares ¯\_(ツ)_/¯
	automat->rule = ruleEdit->getText();
	std::cout << automat->rule;
	AutomatMapper::parseRule(automat->rule, automat);
}