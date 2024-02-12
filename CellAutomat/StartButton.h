﻿#pragma once
#include "Button.h"
#include "Field.h"
#include "FrameEdit.h"

class StartButton : public Button
{
public:
	StartButton(Window* win, Field* destField, SDL_Rect container, char* pathToTexture, char* pathToHover);
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
	SDL_Texture* texture;
	SDL_Texture* textureHover;
	SDL_Renderer* renderer;
	FrameLimitter* frameLimitter;
	FrameEdit* frameEdit;
};