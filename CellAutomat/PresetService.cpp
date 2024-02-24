#include <iostream>

#include "PresetService.h"
#include "PresetDAO.h"

Preset* PresetService::read(const char* pathToFile) {
	Preset* preset = PresetDAO::load(pathToFile);
	std::cout << "Giving back\n";
	return preset;
}

void PresetService::save(const char* pathToFile, Preset* preset) {
	PresetDAO::save(pathToFile, preset);
}