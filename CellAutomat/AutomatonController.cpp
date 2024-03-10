#include "AutomatonController.h"
#include "AutomatMapper.h"

AutomatonController::AutomatonController(AutomatonService* automatonService) {
	this->automatonService = automatonService;
}

void AutomatonController::nextIteration(AutomatDTO* automat) {
	automatonService->next(automat);
}

AutomatDTO* AutomatonController::load(const char* pathToFile) {
	Automat* automat = automatonService->read(pathToFile);
	AutomatDTO* automatDTO = AutomatMapper::mapFrom(automat);
	delete automat;
	return automatDTO;
}

void AutomatonController::save(const char* pathToFile, AutomatDTO* automatDTO) {
	Automat* automat = AutomatMapper::mapTo(automatDTO);
	automatonService->save(pathToFile, automat);
}