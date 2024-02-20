#pragma once
#include "PresetService.h"
#include "PresetDTO.h"

class PresetController
{
public:
	PresetController(PresetService* presetService) : presetService(presetService) {};

	// Preset <-> PresetDTO convertation should be here
	PresetDTO* load(const char* pathToFile);
	void save(const char* pathToFile, PresetDTO* preset);

private:
	PresetService* presetService;
};

