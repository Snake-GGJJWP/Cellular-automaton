#pragma once
#include <iostream>
#include <fstream>


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
	AutomatonService(int, int);
	AutomatonService(int, int, uint8_t**);
	
	void initField();

	void next();

	uint8_t** getField() { return field; }
	void setField(uint8_t**);

	int getWidth() { return w; }
	int getHeight() { return h; }
	void setWidth(int w) { this->w = w; }
	void setHeight(int h) { this->h = h; }

private:
	
	uint8_t** field; // 2d array
	int w, h;

};