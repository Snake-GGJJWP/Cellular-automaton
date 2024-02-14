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
	void handleEvent(SDL_Event*) override;
	void render() override;

	void printName() override { std::cout << "I'm startButton\n"; }

	// It won't work otherwise ¯\_(ツ)_/¯
	void addFrameEdit(FrameEdit* frameEdit) { this->frameEdit = frameEdit; }

private:
	bool isCursorOnButton(int, int) override;

	bool isHovered = false;
	bool isPressed = false;

	Field* field;

	SDL_Rect container;
	SDL_Texture* textureStart;
	SDL_Texture* textureStartHover;
	SDL_Texture* textureStop;
	SDL_Texture* textureStopHover;
	SDL_Renderer* renderer;
	FrameLimitter* frameLimitter;
	FrameEdit* frameEdit;
};