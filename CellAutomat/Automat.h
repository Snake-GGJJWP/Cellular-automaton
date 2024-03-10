#include <iostream>
#include <vector>
#include <string>
#pragma once

class Automat
{
public:
	uint16_t width;
	uint16_t height;
	std::string rule; // B../S.. rule
	
	std::vector<size_t> rleField; // cells represented as RLE
};
