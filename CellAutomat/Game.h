#pragma once
#include <SDL.h>
#include "Automat.h"

class Game
{
public:
	Game(const char *title, int xPos, int yPos, int width, int height, float scaleX, float scaleY, bool fullscreen, int n, int m, bool** field);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	~Game();

private:
	int screenWidth, screenHeight;
	float scaledWidth, scaledHeight; // maybe I remove them later

	bool isRunning = false;
	int frame = 0;

	void initAutomat(int n, int m, bool** field);
	void initAutomat(int n, int m);

	Automat* automat;
	SDL_Window* window;
	SDL_Renderer* renderer;
};