#include "SaveButton.h"
#include "tinyfiledialogs.h"

// I think we don't need Edits here. It's much better to take from Field to avoid occasional broken save files
SaveButton::SaveButton(Window* win, 
					   Field* field,
					   PresetController* presetController, 
					   SDL_Rect cont, 
					   char* pathToTexture, 
					   char* pathToTextureHover) : 
	Button(win, cont),
	field(field),
	presetController(presetController)
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

	PresetDTO* presetDTO = new PresetDTO();

	int w, h;

	//field->saveField((int*)&presetDTO->height, (int*)&presetDTO->width, &presetDTO->field);

	field->saveField(&h, &w, &presetDTO->field);

	presetDTO->height = (uint16_t)h;
	presetDTO->width = (uint16_t)w;
	presetDTO->rule = "B2/S23"; // we'll take it from the field in future;

	//std::cout << presetDTO->height << " " << presetDTO->width << "\n";

	presetController->save(s, presetDTO);
}