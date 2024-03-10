#pragma once
#include "Automat.h"
#include "json.hpp"

using json = nlohmann::json;

class AutomatDAO
{
public:
	static Automat* load(const char* pathToFile);
	static void save(const char* pathToFile, Automat* preset);

private:

};
