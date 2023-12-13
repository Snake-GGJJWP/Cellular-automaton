#include <iostream>
#include <fstream>
#include "Automat.h";

void printMat(bool** mat, int n, int m);

Automat::Automat(int n, int m) {
	// remember field's size
	h = n;
	w = m;

	// Create field;
	// Filled with Trues by default
	initField();

	printMat(field, n, m);
}

Automat::Automat(int n, int m, bool** inField) {
	h = n;
	w = m;

	initField();
	
	// Copy, because someone else will have access to the field otherwise
	setField(inField);

	// printMat(field, h, w);
}

void Automat::next() {
	bool** newField = new bool* [h];
	for (int i = 0; i < h; i++) {
		newField[i] = new bool[w];
	}
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			newField[i][j] = field[i][j];
		}
	}

	int alive = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			alive += ((0 == j) ? false : field[i][j-1]) ? 1 : 0;
			alive += ((w == j+1) ? false : field[i][j+1]) ? 1 : 0;
			alive += ((0 == i) ? false : field[i-1][j]) ? 1 : 0;
			alive += ((h == i+1) ? false : field[i+1][j]) ? 1 : 0;
			alive += (((0 == j) || (0 == i)) ? false : field[i - 1][j - 1]) ? 1 : 0;
			alive += (((w == j+1) || (0 == i)) ? false : field[i - 1][j + 1]) ? 1 : 0;
			alive += (((0 == j) || (h == i+1)) ? false : field[i + 1][j - 1]) ? 1 : 0;
			alive += (((w == j+1) || (h == i+1)) ? false : field[i + 1][j + 1]) ? 1 : 0;

			// Death conditions
			if (alive < 2 || alive > 3) {
				newField[i][j] = false;
			}
			
			// Birth conditions
			else if (alive == 3) {
				newField[i][j] = true;
			}

			alive = 0;
		}
	}

	field = newField;

	// printMat(field, h, w);
}

void Automat::setField(bool** newField) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			field[i][j] = newField[i][j];
		}
	}
}

void Automat::initField() {
	field = new bool* [h];
	for (int i = 0; i < h; i++) {
		field[i] = new bool[w];
	}
}


void printMat(bool** mat, int n, int m) {
	// system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << (mat[i][j] ? "1" : "0") << " ";
		}
		std::cout << std::endl;
	}
}

