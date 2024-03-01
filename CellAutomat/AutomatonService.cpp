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
			alive += ((0 == j) ? false : automat->field[i][j-1]) ? 1 : 0;
			alive += ((automat->width == j+1) ? false : automat->field[i][j+1]) ? 1 : 0;
			alive += ((0 == i) ? false : automat->field[i-1][j]) ? 1 : 0;
			alive += ((automat->height == i+1) ? false : automat->field[i+1][j]) ? 1 : 0;
			alive += (((0 == j) || (0 == i)) ? false : automat->field[i - 1][j - 1]) ? 1 : 0;
			alive += (((automat->width == j+1) || (0 == i)) ? false : automat->field[i - 1][j + 1]) ? 1 : 0;
			alive += (((0 == j) || (automat->height == i+1)) ? false : automat->field[i + 1][j - 1]) ? 1 : 0;
			alive += (((automat->width == j+1) || (automat->height == i+1)) ? false : automat->field[i + 1][j + 1]) ? 1 : 0;

			// Death conditions
			if (automat->field[i][j] == 1 && automat->survive.find(alive) == automat->survive.end()) {
				newField[i][j] = 0;
			}
			
			// Birth conditions
			else if (automat->field[i][j] == 0 && automat->birth.find(alive) != automat->birth.end()) {
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

	// printMat(field, h, w);
}

//void AutomatonService::setField(uint8_t** newField) {
//	field = newField;
//}
//
//void AutomatonService::initField() {
//	field = new uint8_t* [h];
//	for (int i = 0; i < h; i++) {
//		field[i] = new uint8_t[w];
//		for (int j = 0; j < w; j++) {
//			field[i][j] = 0;
//		}
//	}
//}

// Idea:
// Well, we actually just need to take those numbers separated by some non-numeric charachter
// But to keep the rule in a standardized form I think we should check for 'B' and '/S' chars
//bool AutomatonService::setRule(std::string rule) {
//	std::set<uint8_t> newBirth;
//	std::set<uint8_t> newSurvive;
//
//	if (rule.length() == 0) {
//		std::cout << "Empty rule!\n";
//		return false;
//	}
//	if (rule.at(0) != 'B') {
//		std::cout << "Bad rule! Rule must start with \'B\'!\n";
//		return false;
//	}
//
//	auto it = rule.begin() + 1;
//
//	while (*it != '/') 
//	{
//		std::cout << "WE HAVE: " << *it << "\n";
//		if (NUMBERS.find(*it) == NUMBERS.end()) {
//			std::cout << "Bad rule! Conditions must contain numbers!\n";
//			return false;
//		}
//		std::cout << "BIRTH GOT: " << *it - '0' << "\n";
//		newBirth.insert(*it - '0');
//		it++;
//
//		if (it == rule.end()) {
//			std::cout << "Bad rule! Rule must contain survival conditions\n";
//			return false;
//		}
//	}
//
//	if (*(++it) != 'S') {
//		std::cout << "Bad rule! Survival conditions must start with \'S\'!";
//		return false;
//	}
//
//	it++;
//
//	while (it != rule.end())
//	{
//		if (NUMBERS.find(*it) == NUMBERS.end()) {
//			std::cout << "Bad rule! Conditions must contain numbers!\n";
//			return false;
//		}
//		std::cout << "SURVIVE GOT: " << *it - '0' << "\n";
//		newSurvive.insert(*it - '0');
//		it++;
//	}
//
//	birth = newBirth;
//	survive = newSurvive;
//	return true;
//}

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
			std::cout << mat[i][j];
		}
		std::cout << std::endl;
	}
}

