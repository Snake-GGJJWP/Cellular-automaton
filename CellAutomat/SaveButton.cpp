#include "SaveButton.h"
#include "tinyfiledialogs.h"

SaveButton::SaveButton(Window* win, 
					   SDL_Rect cont, 
					   char* pathToTexture, 
					   char* pathToTextureHover) :
	Button(win, cont)
{
	setTexture(pathToTexture);
	setTextureHover(pathToTextureHover);
}

void SaveButton::onClick() {
	char const* patterns[1] = { "*.txt" };
	tinyfd_openFileDialog("TESTING",
							"",
							1,
							patterns,
							"presets",
							0);
}