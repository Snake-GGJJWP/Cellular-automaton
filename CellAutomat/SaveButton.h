#pragma once
#include "Button.h"
#include "Field.h"
#include "TextEdit.h"
#include "NumberEdit.h"
#include "PresetController.h"
#include "PresetDTO.h"

class SaveButton : public Button
{
public:
	SaveButton(Window* win, 
			   Field* field,
			   PresetController* presetController, 
			   SDL_Rect cont, 
			   char* pathToTexture, 
			   char* pathToTextureHover);

private:
	void onClick();
	Field* field;
	PresetController* presetController;
};
