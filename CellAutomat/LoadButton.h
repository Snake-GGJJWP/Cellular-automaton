#pragma once
#include "Button.h"
#include "Field.h"
#include "TextEdit.h"
#include "NumberEdit.h"
#include "ColorPalette.h"
#include "AutomatonController.h"
#include "AutomatDTO.h"

class LoadButton : public Button
{
public:
	LoadButton(Window* win, 
			   Field* field,
			   NumberEdit* widthEdit,
			   NumberEdit* heightEdit,
			   TextEdit* ruleEdit,
			   ColorPalette* colorPalette,
			   AutomatonController* automatonController, 
			   SDL_Rect cont, 
			   char* pathToTexture, 
			   char* pathToTextureHover);

private:
	void onClick();

	Field* field;
	AutomatonController* automatonController;
	NumberEdit* widthEdit;
	NumberEdit* heightEdit;
	TextEdit* ruleEdit;
	ColorPalette* colorPalette;
};
