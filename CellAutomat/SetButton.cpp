#include "SetButton.h"

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

	int newWidth = std::stoi(widthEdit->getText());
	int newHeight = std::stoi(heightEdit->getText());

	int oldWidth = 0, oldHeight = 0;
	uint8_t** oldField;

	field->saveField(&oldHeight, &oldWidth, &oldField);


	uint8_t** newField = new uint8_t*[newHeight];
	for (int i = 0; i < newHeight; i++) {
		newField[i] = new uint8_t[newWidth];

		for (int j = 0; j < newWidth; j++) {
			newField[i][j] = (j < oldWidth && i < oldHeight) ? oldField[i][j] : 0;
		}
	}

	field->loadField(newHeight, newWidth, newField);
}