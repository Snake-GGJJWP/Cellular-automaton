#pragma once
#include "Button.h"
#include "Field.h"
#include "NumberEdit.h"
#include "TextEdit.h"
#include "ColorPalette.h"

class SetButton : public Button
{
public:
	SetButton(Window* win, 
			  Field* field, 
			  NumberEdit* widthEdit,
			  NumberEdit* heightEdit,
			  TextEdit* ruleEdit,
			  ColorPalette* colorPalette,
			  SDL_Rect container, 
			  char* pathToTexture, 
			  char* pathToTextureHover);

private:
	void onClick() override;
	void giveError(std::string text);
	uint8_t min(uint8_t a, uint8_t b);

	Field* field;
	NumberEdit* widthEdit;
	NumberEdit* heightEdit;
	TextEdit* ruleEdit;
	ColorPalette* colorPalette;
};
