#pragma once
#include "Button.h"
#include "Field.h"
#include "PresetController.h"
#include "PresetDTO.h"

class LoadButton : public Button
{
public:
	LoadButton(Window* win, 
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
