#include "PresetController.h"
#include "PresetMapper.h"

PresetDTO* PresetController::load(const char* pathToFile) {
	Preset* preset = presetService->read(pathToFile);
	PresetDTO* presetDTO = PresetMapper::mapFrom(preset);
	delete preset;
	return presetDTO;
}

void PresetController::save(const char* pathToFile, PresetDTO* presetDTO) {
	Preset* preset = PresetMapper::mapTo(presetDTO);
	delete presetDTO;
	presetService->save(pathToFile, preset);
}