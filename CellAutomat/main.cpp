#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>

#include "StartButton.h"
#include "MenuPanel.h"
#include "FrameLimitter.h"

const int WIN_WIDTH = 850;
const int WIN_HEIGHT = 600;

/*
* TODO:
* 1) Make drawing easier
*	1.1) Either make grid or make tiles brighter on hover [+]
*	1.2) Paint-like drawing (pick a color, hold mouth to draw)
* 
* 2) Make customizable automotons
*	2.1) Apply B../S.. rule (string -> rules parser)
*	2.2) Apply generations rules 
*	// --- FOR LATER ---
*	2.3) Apply neighbourhood customization (?) 
*	2.4) Apply Hensel notation
*	2.5) Apply "Larger than life" automatons
*	2.6) Others?
*	// -----------
* 
* 3) Optimize rendering algorithms, frame limitting.
*/

void printMat1(bool** mat, int n, int m) {
	// system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << (mat[i][j] ? "1" : "0") << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]) {
	std::vector<Widget*> widgets;

	std::ifstream file("../presets/12.txt"); // For now we'll read from file

	if (!file) {
		std::cout << "File is not opened" << std::endl;
	}

	int n;
	file >> n;

	int m;
	file >> m;

	float scaleX;
	file >> scaleX;

	float scaleY;
	file >> scaleY;

	bool** field = new bool* [n];
	for (int i = 0; i < n; i++) {
		field[i] = new bool[m];
	}

	//printMat1(field, n, m);

	int p;
	int i = 0;
	for (file >> p; !file.eof(); file >> p) {
		if (i >= n * m) {
			std::cout << "Fuck" << std::endl;
		}
		field[i / m][i % m] = (p ? true : false);
		i++;
	}

	Window* window = new Window(WindowSettings {(char*) "Automaton", 
												SDL_WINDOWPOS_CENTERED, 
												SDL_WINDOWPOS_CENTERED, 
												WIN_WIDTH, 
												WIN_HEIGHT, 
												-1, 
												false});

	AutomatonService* automatonService = new AutomatonService(n, m, field);

	AutomatonController* automatonController = new AutomatonController(automatonService);

	Field* winField = new Field(window,
								automatonController,
								SDL_Rect{ 0, 0, 600, 600 });
	StartButton* startButton = new StartButton(window, 
											   winField, 
											   SDL_Rect {620, 20, 210, 70}, 
										       (char*)"../resources/StartButton.bmp");
	MenuPanel* menuPanel = new MenuPanel(window,
										 SDL_Rect{ 600, 0, 250, 600 },
										 SDL_Color{ 255, 255, 255, 255 });


	// Order is important!!!
	widgets.push_back(winField);
	widgets.push_back(menuPanel);
	widgets.push_back(startButton);

	while (window->running()) {

		// Limit framerate
		// Problem: It affects handleEvent functions; it should affect only rendering and updating.
		// Heuristic solution: make framelimitter class controlled by start/stop button;
		// when the game is in editting state - remove frame limitting by putting timeskip = 0s;
		// when the game is in playing state  - set frame limitting at ~60 fps by putting timeskip = 1000/60 s
		/*std::this_thread::sleep_for(std::chrono::milliseconds(30));*/

		// (1) Render and present all the stuff;
		window->cleanRender();
		window->render();

		for (auto widget : widgets) {
			widget->render();
		}

		window->presentRender();

		// (2) Update
		for (auto widget : widgets) {
			widget->update();
		}

		window->update();

		// (3) HandleEvents;
		static SDL_Event event;
		SDL_PollEvent(&event);

		for (auto widget : widgets) {
			widget->handleEvent(&event);
		}

		window->handleEvent(&event);

	}

	window->clean();

	return 0;
}