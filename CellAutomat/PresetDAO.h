#pragma once
#include "Preset.h"
#include "json.hpp"

using json = nlohmann::json;

class PresetDAO
{
public:
	static Preset* load(const char* pathToFile);
	static void save(const char* pathToFile, Preset* preset);

private:

};
