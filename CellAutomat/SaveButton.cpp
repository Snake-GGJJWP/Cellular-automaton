#include "SaveButton.h"
#include "tinyfiledialogs.h"

// I think we don't need Edits here. It's much better to take from Field to avoid occasional broken save files
SaveButton::SaveButton(Window* win, 
					   Field* field,
					   AutomatonController* automatonController, 
					   SDL_Rect cont, 
					   char* pathToTexture, 
					   char* pathToTextureHover) : 
	Button(win, cont),
	field(field),
	automatonController(automatonController)
{
	setTexture(pathToTexture);
	setTextureHover(pathToTextureHover);
}

void SaveButton::onClick() {
	char const* patterns[1] = { "*.json" };
	char* s = tinyfd_saveFileDialog("TESTING",
									"save.json",
									1,
									patterns,
									"presets");
	if (s == NULL) {
		return;
	}

	AutomatDTO* automatDTO = field->getAutomat();

	automatonController->save(s, automatDTO);
}