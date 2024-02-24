#include <vector>
#include "PresetMapper.h"

const uint16_t MAX_WIDTH = 600;
const uint16_t MIN_WIDTH = 1;
const uint16_t MAX_HEIGHT = 600;
const uint16_t MIN_HEIGHT = 1;

void printMat2(uint8_t** mat, int n, int m) {
	// system("CLS");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << (mat[i][j] ? "1" : "0") << " ";
		}
		std::cout << std::endl;
	}
}

Preset* PresetMapper::mapTo(PresetDTO* presetDTO) {
	if (presetDTO == NULL) {
		return NULL;
	}

	Preset* preset = new Preset();

	// ## WIDTH ##
	if (presetDTO->width > MAX_WIDTH || presetDTO->width < MIN_WIDTH) {
		std::cout << "Invalid width value\n";
		return NULL;
	}
	preset->width = presetDTO->width;

	// ## HEIGHT ##
	if (presetDTO->height > MAX_HEIGHT || presetDTO->height < MIN_HEIGHT) {
		std::cout << "Invalid height value\n";
		return NULL;
	}
	preset->height = presetDTO->height;

	// ## RULE ##
	preset->rule = presetDTO->rule;

	// ## 2D ARRAY -> RLE ## 
	std::vector<size_t> arr;
	auto curNum = presetDTO->field[0][0];
	int count = 0;
	for (int i = 0; i < presetDTO->height; i++) {
		for (int j = 0; j < presetDTO->width; j++) {
			if (curNum != presetDTO->field[i][j]) {
				std::cout << curNum << " " << count << "\n";
				arr.push_back(curNum);
				arr.push_back(count);
				curNum = presetDTO->field[i][j];
				count = 0;
			}
			count++;
		}
	}
	arr.push_back(curNum);
	arr.push_back(count);

	preset->rleField = arr;

	for (auto var : preset->rleField) {
		std::cout << var << " ";
	}
	std::cout << "\n";

	return preset;
}

PresetDTO* PresetMapper::mapFrom(Preset* preset) {
	if (preset == NULL) {
		return NULL;
	}

	PresetDTO* presetDTO = new PresetDTO();

	// ## WIDTH ##
	if (preset->width > MAX_WIDTH || preset->width < MIN_WIDTH) {
		std::cout << "Invalid width value\n";
		return NULL;
	}
	presetDTO->width = preset->width;

	// ## HEIGHT ##
	if (preset->height > MAX_HEIGHT || preset->height < MIN_HEIGHT) {
		std::cout << (preset->height > MAX_HEIGHT ? "True" : "False") << "Invalid height value\n";
		std::cout << preset->height - MAX_HEIGHT << " Invalid height value\n";
		return NULL;
	}
	presetDTO->height = preset->height;

	// ## RULE ##
	presetDTO->rule = preset->rule;

	// ## RLE -> 2D ARRAY ##
	if (preset->rleField.size() == 0 || preset->rleField.size() % 2 != 0) {
		std::cout << "Invalid field preset\n";
		return NULL;
	}

	std::cout << presetDTO->height << " " << presetDTO->width << "\n";

	// Init field
	uint8_t** field = new uint8_t* [presetDTO->height];
	// for (int i = 0; i < presetDTO->height; field[i++] = new uint8_t[presetDTO->width]) {}
	for (int i = 0; i < presetDTO->height; i++) {
		field[i] = new uint8_t[presetDTO->width];
	}

	int k = 0;
	for (int i = 0; i < preset->rleField.size(); i += 2) {
		size_t curNum = preset->rleField[i];
		int count = preset->rleField[i + 1];

		if (k + count > preset->width * preset->height) {
			std::cout << "Field overflow\n";
			return NULL;
		}

		for (int j = 0; j < count; j++) {
			field[(k + j) / preset->width][(k + j) % preset->width] = curNum;
		}
		k += count;
	}

	//printMat2(field, preset->height, preset->width);

	presetDTO->field = field;

	return presetDTO;
}