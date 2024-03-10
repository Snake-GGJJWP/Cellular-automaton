#pragma once
#include "AutomatonService.h"
#include "AutomatDTO.h"

class AutomatonController
{
public:
	AutomatonController(AutomatonService* automatonService);

	void nextIteration(AutomatDTO* automat);
	AutomatDTO* load(const char* pathToFile);
	void save(const char* pathToFile, AutomatDTO* preset);
	//uint8_t** getField() { return automatonService->getField(); }
	//void setField(uint8_t** field) { automatonService->setField(field); }
	//int getHeight() { return automatonService->getHeight(); }
	//int getWidth() { return automatonService->getWidth(); }
	//void setHeight(int height) { automatonService->setHeight(height); }
	//void setWidth(int width) { automatonService->setWidth(width); }
	//void setRule(std::string rule) { automatonService->setRule(rule); }

private:
	AutomatonService* automatonService;
};