#include <fstream>
#include <chrono>
#include <thread>
#include <vector>

#include "StartButton.h"
#include "MenuPanel.h"
#include "FrameLimitter.h"
#include "Label.h"
#include "ColorPalette.h"

const int WIN_WIDTH = 850;
const int WIN_HEIGHT = 600;
const int WIN_FPS = -1;


// ## MOST NOTABLE BUGS DURING DEVELOPMENT ##

/*
* NOTE TO TOMORROW SELF:
* There's a bug in FrameEdit or Edit
* I have no idea why but the app keeps crashing if I use them...
* First idea: Memory Leak, RAM problems. Most likely that's not the case.
* 
* FACT 1: If I init Edit after StartButton it works ok. If vice-versa the bug appears
* FACT 2: The bug doesn't appear if I remove edit textureStart
* FACT 3: The bug appears when I try to create a textureStart from font
* 
* Conclusion:
* Apparently, it was a memory access error caused by library function
* during textureStart creation... It will stay as one of the bugs I couldn't fix...
*/

/*
* ANOTHER INTERESTING BUG:
* If I try to init fonts before widgets it crashes (with the same error code -1073741819)
* Error appears when trying to create Texture for hovered StartButton...
* 
* But if I init them jsut before FrameEdit initialization it works ok...
*/

/*
* TODO:
* 1) Make drawing easier [+]
*	1.1) Either make grid or make tiles brighter on hover [+]
*	1.2) Paint-like drawing (pick a color, hold mouth to draw) [+]
* 
* 2) Make prettier GUI [+]
* 
* 3) Make customizable automotons
*	3.0) Make editable field. (size, pallete)
*	3.1) Apply B../S.. rule (string -> rules parser)
*	3.2) Apply generations rules 
*	// --- FOR LATER ---
*	3.3) Apply neighbourhood customization (?) 
*	3.4) Apply Hensel notation
*	3.5) Apply "Larger than life" automatons
*	3.6) Others?
*	// -----------
* 
* 4) Optimize rendering algorithms, frame limitting[+-]. Add flag to widgits which tells if they need rendering.
*	 Update the flag in handleEvents() or update().
* 
* 5) Make exception handling
*/

// Make another class which would start things we need?
void initLibs() {
	// Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL...\n" << SDL_GetError() << "\n";
		return;
	}

	// Start TTF
	if (TTF_Init() != 0) {
		std::cout << "Failed to initialize TTF...\n" << TTF_GetError() << "\n";
	}

	// Start SDL_image
	if (!IMG_Init(IMG_INIT_JPG)) {
		std::cout << "Failed to initialize IMG...\n" << IMG_GetError() << "\n";
	}

	SDL_StartTextInput();
}

TTF_Font* loadFont(std::string ttfFile, int fontSize) {
	TTF_Font* font = TTF_OpenFont(ttfFile.c_str(), fontSize);
	if (font == NULL) {
		std::cout << "FAILED TO LOAD THE FONT\n";
		std::cout << TTF_GetError();
		throw std::invalid_argument("path to .ttf file is unreachable");
	}
	return font;
}

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
	initLibs();

	std::vector<Widget*> widgets;


	// ## PRESET LOAD (TEMPORAL) ##
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

	// ## FONTS ##

	// ## WIDGETS INITIALIZATION ##
	Window* window = new Window(WindowSettings {(char*) "Automaton", 
												SDL_WINDOWPOS_CENTERED, 
												SDL_WINDOWPOS_CENTERED, 
												WIN_WIDTH, 
												WIN_HEIGHT, 
												WIN_FPS, 
												false});

	AutomatonService* automatonService = new AutomatonService(n, m, field);

	AutomatonController* automatonController = new AutomatonController(automatonService);

	Field* winField = new Field(window,
								automatonController,
								SDL_Rect{ 0, 0, 600, 600 });

	StartButton* startButton = new StartButton(window, 
											   winField,
											   SDL_Rect {620, 20, 210, 70}, 
										       (char*)"../resources/StartButtonPurple.jpg",
										       (char*)"../resources/StartButtonPurpleOnHover.jpg",
											   (char*)"../resources/StopButtonPurple.jpg",
											   (char*)"../resources/StopButtonPurpleOnHover.jpg");
	std::cout << "CREATE FONT!\n";

	TTF_Font* PIXEL_30 = loadFont("../resources/PixelDigivolve.ttf", 30);

	FrameEdit* frameEdit = new FrameEdit(window,
										 SDL_Rect{ 700, 110, 130, 70 },
										 SDL_Color{ 255, 255, 255, 255 },
										 PIXEL_30,
										 new std::string("../resources/editBackground.jpg"),
										 new std::string("60"));

	Label* fpsLabel = new Label(window,
								SDL_Rect{ 620, 110, 170, 70 },
								SDL_Color{ 255, 255, 255, 255 },
								PIXEL_30,
								"FPS");

	std::vector<SDL_Color> colors = { SDL_Color{0,0,0,255},
									  SDL_Color{255,255,255,255} };

	ColorPalette* colorPalette = new ColorPalette(window,
												  winField,
												  SDL_Rect{620,200,210,50},
												  colors,
												  30);

	MenuPanel* menuPanel = new MenuPanel(window,
										 SDL_Rect{ 600, 0, 250, 600 },
										 (char*)"../resources/MenuPurpleNew.jpg");

	startButton->addFrameEdit(frameEdit);


	// Order is important!!!
	widgets.push_back(winField);
	widgets.push_back(menuPanel);
	widgets.push_back(startButton);
	widgets.push_back(frameEdit);
	widgets.push_back(fpsLabel);
	widgets.push_back(colorPalette);

	// ## MAIN LOOP
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