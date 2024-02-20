#pragma once
#include <iostream>

class PresetDTO
{
public:
	uint16_t width; // [1, 600]
	uint16_t height; // [1, 600] 
	std::string rule; // B../S.. rule

	uint8_t** field; // cells represented as 2d array

private:

};
