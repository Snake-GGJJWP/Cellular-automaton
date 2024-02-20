#pragma once
#include "AutomatonService.h"

class AutomatonController
{
public:
	AutomatonController(AutomatonService* automatonService);

	uint8_t** getNextIteration();
	uint8_t** getField() { return automatonService->getField(); }
	void setField(uint8_t** field) { automatonService->setField(field); }
	int getHeight() { return automatonService->getHeight(); }
	int getWidth() { return automatonService->getWidth(); }
	void setHeight(int height) { automatonService->setHeight(height); }
	void setWidth(int width) { automatonService->setWidth(width); }

private:
	AutomatonService* automatonService;
};