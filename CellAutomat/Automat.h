#pragma once

// Maybe use generics?
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
class Automat
{
public:
	Automat(int, int);
	Automat(int, int, bool**);
	
	void initField();

	void next();

	bool** getField() { return field; } // but then anyone can access the field... shit
	void setField(bool**);

	int getWidth() { return w; }
	int getHeight() { return h; }

private:
	
	// We use bool because we represent only 2 states: live or dead. Save memory.
	bool** field; // 2d array
	int w, h;

};