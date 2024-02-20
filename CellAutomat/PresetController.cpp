#include "PresetController.h"
#include "PresetMapper.h"

PresetDTO* PresetController::load(const char* pathToFile) {
	Preset* preset = presetService->read(pathToFile);
	return PresetMapper::mapFrom(preset);
}

void PresetController::save(const char* pathToFile, PresetDTO* presetDTO) {
	Preset* preset = PresetMapper::mapTo(presetDTO);
	presetService->save(pathToFile, preset);
}