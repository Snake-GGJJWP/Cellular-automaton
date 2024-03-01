#pragma once
#include <iostream>
#include <set>

class AutomatDTO
{
public:
	uint16_t width; // [1, 600]
	uint16_t height; // [1, 600] 
	std::string rule; // B../S.. rule

	std::set<uint8_t> birth; // [0..8] number of cells for cell to be born
	std::set<uint8_t> survive; // [0..8] number of cells for cell to survive
	uint8_t generations;

	uint8_t** field; // cells represented as 2d array

	~AutomatDTO() {
		for (int i = 0; i < height; i++) {
			delete[] field[i];
		}
		delete[] field;
	}

private:

};


