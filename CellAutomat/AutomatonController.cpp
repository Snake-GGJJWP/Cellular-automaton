#include "AutomatonController.h"

AutomatonController::AutomatonController(AutomatonService* automatonService) {
	this->automatonService = automatonService;
}

uint8_t** AutomatonController::getNextIteration() {
	automatonService->next();
	return automatonService->getField();
}