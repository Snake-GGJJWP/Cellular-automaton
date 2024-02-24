#pragma once
#include "Button.h"
#include "Field.h"
#include "NumberEdit.h"
#include "TextEdit.h"

class SetButton : public Button
{
public:
	SetButton(Window* win, 
			  Field* field, 
			  NumberEdit* widthEdit,
			  NumberEdit* heightEdit,
			  TextEdit* ruleEdit,
			  SDL_Rect container, 
			  char* pathToTexture, 
			  char* pathToTextureHover);

	void onClick() override;

private:
	Field* field;
	NumberEdit* widthEdit;
	NumberEdit* heightEdit;
	TextEdit* ruleEdit;
};
