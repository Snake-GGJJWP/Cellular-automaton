#pragma once
#include "Button.h"
#include "Field.h"

class ClearButton : public Button
{
public:
	ClearButton(Window* win,
				Field* field,
				SDL_Rect container,
				char* pathToTexture,
				char* pathToTextureHover) :
		Button(win, container),
		field(field)
	{
		setTexture(pathToTexture);
		setTextureHover(pathToTextureHover);
	}

	void onClick() override {
		if (field->running()) {
			return;
		}

		field->clearField();
	}

private:
	Field* field;
};
