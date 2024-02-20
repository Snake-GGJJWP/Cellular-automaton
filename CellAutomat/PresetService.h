#pragma once
#include <string>
#include "Preset.h"

class PresetService
{
public:

	// change json to Preset model later
	Preset* read(const char* pathToFile); 
	void save(const char* pathToFile, Preset* preset);
	

private:

};
