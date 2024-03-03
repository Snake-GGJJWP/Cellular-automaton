#include "AutomatonService.h"
#include "AutomatDAO.h"

void printMat(uint8_t** mat, int n, int m);

//AutomatonService::AutomatonService(int n, int m) {
//	// remember field's size
//	h = n;
//	w = m;
//
//	// Create field;
//	// Filled with Trues by default
//	initField();
//
//	printMat(field, h, w);
//}
//
//AutomatonService::AutomatonService(int n, int m, uint8_t** inField) {
//	h = n;
//	w = m;
//
//	initField();
//	
//	// Copy, because someone else will have access to the field otherwise
//	setField(inField);
//
//	//printMat(field, h, w);
//}

void AutomatonService::next(AutomatDTO* automat) {

	// printMat(automat->field, automat->height, automat->width);

	uint8_t** newField = new uint8_t* [automat->height];
	for (int i = 0; i < automat->height; i++) {
		newField[i] = new uint8_t[automat->width];
	}
	
	for (int i = 0; i < automat->height; i++) {
		for (int j = 0; j < automat->width; j++) {
			newField[i][j] = automat->field[i][j];
		}
	}

	int alive = 0;
	for (int i = 0; i < automat->height; i++) {
		for (int j = 0; j < automat->width; j++) {

			// Counting living cells
			alive += ((0 == j) ? false : automat->field[i][j-1] == 1) ? 1 : 0;
			alive += ((automat->width == j+1) ? false : automat->field[i][j+1] == 1) ? 1 : 0;
			alive += ((0 == i) ? false : automat->field[i-1][j] == 1) ? 1 : 0;
			alive += ((automat->height == i+1) ? false : automat->field[i+1][j] == 1) ? 1 : 0;
			alive += (((0 == j) || (0 == i)) ? false : automat->field[i - 1][j - 1] == 1) ? 1 : 0;
			alive += (((automat->width == j+1) || (0 == i)) ? false : automat->field[i - 1][j + 1] == 1) ? 1 : 0;
			alive += (((0 == j) || (automat->height == i+1)) ? false : automat->field[i + 1][j - 1] == 1) ? 1 : 0;
			alive += (((automat->width == j+1) || (automat->height == i+1)) ? false : automat->field[i + 1][j + 1] == 1) ? 1 : 0;

			// Aging conditions
			bool isEnoughToSurvive = automat->survive.find(alive) != automat->survive.end();
			bool isCellAlive = automat->field[i][j] == 1;
			bool isAged = (isCellAlive && !isEnoughToSurvive) || automat->field[i][j] > 1;
			if (isAged) {
				newField[i][j] = automat->field[i][j] + 1;
			}

			// Death conditions
			bool isDead = newField[i][j] > (automat->generations-1);
			if (isDead) {
				newField[i][j] = 0;
			}
			
			// Birth conditions
			bool isCellDead = automat->field[i][j] == 0;
			bool isEnoughToBirth = automat->birth.find(alive) != automat->birth.end();
			if (isCellDead && isEnoughToBirth) {
				newField[i][j] = 1;
			}

			alive = 0;
		}
	}

	// Free memory
	for (int i = 0; i < automat->height; i++)
	{
		delete[] automat->field[i];
	}

	delete[] automat->field;

	automat->field = newField;
}

Automat* AutomatonService::read(const char* pathToFile) {
	Automat* automat = AutomatDAO::load(pathToFile);
	std::cout << "Giving back\n";
	return automat;
}

void AutomatonService::save(const char* pathToFile, Automat* automat) {
	AutomatDAO::save(pathToFile, automat);
}


void printMat(uint8_t** mat, int n, int m) {
	// system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << (int)mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

