#pragma once
#include "Button.h"
#include "Field.h"
#include "FrameEdit.h"

class StartButton : public Button
{
public:
	StartButton(Window* win, 
				Field* destField, 
				SDL_Rect container, 
				char* pathToStartTexture, 
				char* pathToStartHover,
				char* pathToStopTexture,
				char* pathToStopHover);
	void render() override;

	// It won't work otherwise ¯\_(ツ)_/¯
	void addFrameEdit(FrameEdit* frameEdit) { this->frameEdit = frameEdit; }

private:
	void onClick() override;

	Field* field;

	SDL_Texture* textureStart;
	SDL_Texture* textureStartHover;
	SDL_Texture* textureStop;
	SDL_Texture* textureStopHover;
	FrameLimitter* frameLimitter;
	FrameEdit* frameEdit;
};