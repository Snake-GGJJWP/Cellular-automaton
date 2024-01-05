#pragma once
#include <vector>

#include <SDL.h>

/*
* Stands for working with a window and provide its children with the renderer
*/
class Window
{
public:
	Window(const char *title, int xPos, int yPos, int width, int height, float scaleX, float scaleY, bool fullscreen);

	void handleEvent(const SDL_Event* event);
	void update();
	void render();
	void cleanRender();
	void presentRender();
	void clean();

	bool running() { return isRunning; }

	SDL_Renderer* getRenderer() { return renderer; }

	~Window();

private:
	int screenWidth, screenHeight;
	float scaledWidth, scaledHeight; // maybe I remove them later

	bool isRunning = false;
	int frame = 0;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};