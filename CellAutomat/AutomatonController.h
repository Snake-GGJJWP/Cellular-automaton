#pragma once
#include "AutomatonService.h"

class AutomatonController
{
public:
	AutomatonController(AutomatonService* automatonService);

	bool** getNextIteration();
	bool** getField() { return automatonService->getField(); }
	void setField(bool** field) { automatonService->setField(field); }
	int getHeight() { return automatonService->getHeight(); }
	int getWidth() { return automatonService->getWidth(); }

private:
	AutomatonService* automatonService;
};