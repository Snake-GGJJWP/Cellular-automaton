#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "StartButton.h"
#include "MenuPanel.h"

const int WIN_WIDTH = 850;
const int WIN_HEIGHT = 600;

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

	std::ifstream file("../presets/9.txt");

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
		// std::cout << "TEST: " << i / n << " " << i % m << " " << p << std::endl;
		i++;
	}

	// printMat1(field, n, m);



	//Window* window = new Window("test", 
	//				SDL_WINDOWPOS_CENTERED, 
	//				SDL_WINDOWPOS_CENTERED, 
	//				m*scaleX, 
	//				n*scaleY, 
	//				scaleX, 
	//				scaleY, 
	//				0);

	Window* window = new Window("test",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					WIN_WIDTH,
					WIN_HEIGHT,
					scaleX,
					scaleY,
					1);

	AutomatonService* automatonService = new AutomatonService(n, m, field);

	AutomatonController* automatonController = new AutomatonController(automatonService);

	Field* winField = new Field(window, 
								automatonController, 
								SDL_Rect{0, 0, (int)(m * scaleX), (int) (n * scaleY)});
	StartButton* startButton = new StartButton(window, 
											   winField, 
											   SDL_Rect {620, 20, 210, 70}, 
										       (char*)"../resources/StartButton.bmp");
	MenuPanel* menuPanel = new MenuPanel(window,
										 SDL_Rect{ 600, 0, 250, 600 },
										 SDL_Color{ 255, 255, 255, 0 });


	// Order is important!!!
	widgets.push_back(winField);
	widgets.push_back(menuPanel);
	widgets.push_back(startButton);

	while (window->running()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(30));

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