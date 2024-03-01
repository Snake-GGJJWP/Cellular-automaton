#pragma once
#include "Automat.h"
#include "AutomatDTO.h"

class AutomatMapper
{
public:
	static Automat* mapTo(AutomatDTO* presetDTO);
	static AutomatDTO* mapFrom(Automat* preset);

	static bool parseRule(std::string rule, AutomatDTO* automatDTO);

private:

	inline static const std::set <char> NUMBERS = { '1','2','3','4','5','6','7','8','9','0' };
};
