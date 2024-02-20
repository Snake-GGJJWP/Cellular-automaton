#pragma once
#include "Preset.h"
#include "PresetDTO.h"

class PresetMapper
{
public:
	static Preset* mapTo(PresetDTO* presetDTO);
	static PresetDTO* mapFrom(Preset* preset);

private:

};
