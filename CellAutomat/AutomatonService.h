#pragma once
#include <iostream>
#include <set>
#include "Automat.h"
#include "AutomatDTO.h"


/*
* TODO:
* *Make the Automat interface and implent it to different types of Automat (INT, anisotrop, generations etc)
* *Use generic class where T represents type of field
* *Make custom neighbourhoods (for now it's Moore neighbourhood)
* *Make B/S notation
* *Make that user can draw patterns
* *Implement speed adjust in app
* *Implement step by step mode
*/
class AutomatonService
{
public:
	//AutomatonService();
	
	//void initField();

	void next(AutomatDTO* automatDTO);

	Automat* read(const char* pathToFile);
	void save(const char* pathToFile, Automat* preset);

	//uint8_t** getField() { return field; }
	//int getWidth() { return w; }
	//int getHeight() { return h; }

	//// Do we need to check these values?
	//void setField(uint8_t**);
	//void setWidth(int w) { this->w = w; }
	//void setHeight(int h) { this->h = h; }

	//bool setRule(std::string rule);

private:
	
	//uint8_t** field; // 2d array
	//int w, h;
	//std::set<uint8_t> birth; // number of cells to create a cell
	//std::set<uint8_t> survive; // number of cells for cell to survive

	const std::set <char> NUMBERS = { '1','2','3','4','5','6','7','8','9','0' };
};