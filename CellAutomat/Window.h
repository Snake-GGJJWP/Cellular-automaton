#pragma once

#include <SDL.h>
#include "FrameLimitter.h"

typedef struct {
	char* title;
	int xPos;
	int yPos;
	int width;
	int height;
	int fps; 
	bool fullscreen;
} WindowSettings;

/*
* Stands for working with a window and provide its children with the renderer
*/
class Window
{
public:
	Window(WindowSettings winSet);

	void handleEvent(const SDL_Event* event);
	void update();
	void render();
	void cleanRender();
	void presentRender();
	void clean();

	bool running() { return isRunning; }

	void setFPS(int fps);

	SDL_Renderer* getRenderer() { return renderer; }
	FrameLimitter* getFrameLimitter() { return frameLimitter; }

	~Window();

private:
	int screenWidth, screenHeight;

	bool isRunning = false;
	int frame = 0;

	FrameLimitter* frameLimitter = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};