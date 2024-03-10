#pragma once
#include "Button.h"
#include "Field.h"
#include "TextEdit.h"
#include "NumberEdit.h"
#include "AutomatonController.h"
#include "AutomatDTO.h"

class SaveButton : public Button
{
public:
	SaveButton(Window* win, 
			   Field* field,
			   AutomatonController* automatonController, 
			   SDL_Rect cont, 
			   char* pathToTexture, 
			   char* pathToTextureHover);

private:
	void onClick();
	Field* field;
	AutomatonController* automatonController;
};
