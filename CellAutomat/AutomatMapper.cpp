#include <vector>
#include "AutomatMapper.h"

const uint16_t MAX_WIDTH = 600;
const uint16_t MIN_WIDTH = 1;
const uint16_t MAX_HEIGHT = 600;
const uint16_t MIN_HEIGHT = 1;
const uint8_t MAX_GENERATIONS = 60;
const uint8_t MIN_GENERATIONS = 1;

Automat* AutomatMapper::mapTo(AutomatDTO* automatDTO) {
	if (automatDTO == NULL) {
		return NULL;
	}

	Automat* automat = new Automat();

	// ## WIDTH ##
	if (automatDTO->width > MAX_WIDTH || automatDTO->width < MIN_WIDTH) {
		std::cout << "Invalid width value\n";
		return NULL;
	}
	automat->width = automatDTO->width;

	// ## HEIGHT ##
	if (automatDTO->height > MAX_HEIGHT || automatDTO->height < MIN_HEIGHT) {
		std::cout << "Invalid height value\n";
		return NULL;
	}
	automat->height = automatDTO->height;

	// ## RULE ##
	automat->rule = automatDTO->rule;

	// ## 2D ARRAY -> RLE ## 
	std::vector<size_t> arr;
	auto curNum = automatDTO->field[0][0];
	int count = 0;
	for (int i = 0; i < automatDTO->height; i++) {
		for (int j = 0; j < automatDTO->width; j++) {
			if (curNum != automatDTO->field[i][j]) {
				arr.push_back(curNum);
				arr.push_back(count);
				curNum = automatDTO->field[i][j];
				count = 0;
			}
			count++;
		}
	}
	arr.push_back(curNum);
	arr.push_back(count);

	automat->rleField = arr;

	return automat;
}

AutomatDTO* AutomatMapper::mapFrom(Automat* automat) {
	if (automat == NULL) {
		return NULL;
	}

	AutomatDTO* automatDTO = new AutomatDTO();

	// ## WIDTH ##
	if (automat->width > MAX_WIDTH || automat->width < MIN_WIDTH) {
		std::cout << "Invalid width value\n";
		return NULL;
	}
	automatDTO->width = automat->width;

	// ## HEIGHT ##
	if (automat->height > MAX_HEIGHT || automat->height < MIN_HEIGHT) {
		std::cout << (automat->height > MAX_HEIGHT ? "True" : "False") << "Invalid height value\n";
		std::cout << automat->height - MAX_HEIGHT << " Invalid height value\n";
		return NULL;
	}
	automatDTO->height = automat->height;

	// ## RULE ##
	automatDTO->rule = automat->rule;
	if (!parseRule(automat->rule, automatDTO)) {
		return NULL;
	}

	// ## RLE -> 2D ARRAY ##
	if (automat->rleField.size() == 0 || automat->rleField.size() % 2 != 0) {
		std::cout << "Invalid field preset\n";
		return NULL;
	}

	std::cout << automatDTO->height << " " << automatDTO->width << "\n";

	// Init field
	uint8_t** field = new uint8_t* [automatDTO->height];
	// for (int i = 0; i < automatDTO->height; field[i++] = new uint8_t[automatDTO->width]) {}
	for (int i = 0; i < automatDTO->height; i++) {
		field[i] = new uint8_t[automatDTO->width];
	}

	int k = 0;
	for (int i = 0; i < automat->rleField.size(); i += 2) {
		size_t curNum = automat->rleField[i];
		int count = automat->rleField[i + 1];

		if (k + count > automat->width * automat->height) {
			std::cout << "Field overflow\n";
			return NULL;
		}

		for (int j = 0; j < count; j++) {
			field[(k + j) / automat->width][(k + j) % automat->width] = curNum;
		}
		k += count;
	}

	automatDTO->field = field;

	return automatDTO;
}

// Idea:
// Well, we actually just need to take those numbers separated by some non-numeric charachter
// But to keep the rule in a standardized form I think we should check for 'B' and '/S' chars
bool AutomatMapper::parseRule(std::string rule, AutomatDTO* automatDTO) {
	std::set<uint8_t> newBirth;
	std::set<uint8_t> newSurvive;
	int newGen = 0;

	if (rule.length() == 0) {
		std::cout << "Empty rule!\n";
		return false;
	}

	if (toupper(rule.at(0)) != 'B') {
		std::cout << "Bad rule! Rule must start with \'B\'!\n";
		return false;
	}

	auto it = rule.begin() + 1;

	// Get birth conditions
	while (*it != '/')
	{
		std::cout << "WE HAVE: " << *it << "\n";
		if (NUMBERS.find(*it) == NUMBERS.end()) {
			std::cout << "Bad rule! Conditions must contain numbers!\n";
			return false;
		}
		std::cout << "BIRTH GOT: " << *it - '0' << "\n";
		newBirth.insert(*it - '0');
		it++;

		if (it == rule.end()) {
			std::cout << "Bad rule! Rule must contain survival conditions\n";
			return false;
		}
	}

	if (toupper(*(++it)) != 'S') {
		std::cout << "Bad rule! Survival conditions must start with \'S\'!";
		return false;
	}

	it++;

	// Get survival conditions
	while (it != rule.end() && *it != '/')
	{
		if (NUMBERS.find(*it) == NUMBERS.end()) {
			std::cout << "Bad rule! Conditions must contain numbers!\n";
			return false;
		}
		std::cout << "SURVIVE GOT: " << *it - '0' << "\n";
		newSurvive.insert(*it - '0');
		it++;
	}

	if (it == rule.end()) {
		std::cout << "No generations\n";
		automatDTO->birth = newBirth;
		automatDTO->survive = newSurvive;
		automatDTO->generations = 2;
		return true;
	}

	// Get generations
	it++;
	while (it != rule.end()) {
		if (NUMBERS.find(*it) == NUMBERS.end()) {
			std::cout << "Bad rule! Conditions must contain numbers!\n";
			return false;
		}
		newGen = newGen*10 + (*it - '0');
		it++;
	}

	if (newGen < MIN_GENERATIONS || newGen > MAX_GENERATIONS) {
		std::cout << "Invalid number of generations!\n";
		return false;
	}

	automatDTO->generations = newGen;
	automatDTO->birth = newBirth;
	automatDTO->survive = newSurvive;
	return true;
}