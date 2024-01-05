#pragma once
#include "AutomatonService.h"

class AutomatonController
{
public:
	AutomatonController(AutomatonService* automatonService);

	bool** getNextIteration();
	int getHeight() { return automatonService->getHeight(); }
	int getWidth() { return automatonService->getWidth(); }

private:
	AutomatonService* automatonService;
};