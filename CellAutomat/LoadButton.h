#pragma once
#include "Button.h"
#include "Field.h"
#include "TextEdit.h"
#include "NumberEdit.h"
#include "PresetController.h"
#include "PresetDTO.h"

class LoadButton : public Button
{
public:
	LoadButton(Window* win, 
			   Field* field,
			   NumberEdit* widthEdit,
			   NumberEdit* heightEdit,
			   TextEdit* ruleEdit,
			   PresetController* presetController, 
			   SDL_Rect cont, 
			   char* pathToTexture, 
			   char* pathToTextureHover);

private:
	void onClick();

	Field* field;
	PresetController* presetController;
	NumberEdit* widthEdit;
	NumberEdit* heightEdit;
	TextEdit* ruleEdit;
};
