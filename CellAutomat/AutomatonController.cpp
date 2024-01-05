#include "AutomatonController.h"

// It's like a controller? Maybe it's better to make a specific controllers for all widgets?
AutomatonController::AutomatonController(AutomatonService* automatonService) {
	this->automatonService = automatonService;
}

bool** AutomatonController::getNextIteration() {
	automatonService->next();
	return automatonService->getField();
}