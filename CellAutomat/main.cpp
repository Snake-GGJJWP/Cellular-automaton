#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Game.h"

Game* game = nullptr;
// Automat* automat = nullptr;

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
	std::ifstream file("D:\\Programming\\1) projects\\CellAutomat\\presets\\5.txt");

	if (!file) {
		std::cout << "File is not opened" << std::endl;
	}

	int n;
	file >> n;

	int m;
	file >> m;

	int scaleX;
	file >> scaleX;

	int scaleY;
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

	// field[n - 1][m - 1] = (p ? true : false);

	game = new Game("test", 
					SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOWPOS_CENTERED, 
					m*scaleX, 
					n*scaleY, 
					scaleX, 
					scaleY, 
					0, 
					n, 
					m, 
					field);

	char a;
	while (game->running()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	

	//// printMat1(field, n, m);

	//automat = new Automat(n, m, field);
	//char dummy;

	//for (int i = 0;; i++) {
	//	std::this_thread::sleep_for(std::chrono::milliseconds(33));
	//	system("CLS");
	//	automat->next();
	//}

	return 0;
}