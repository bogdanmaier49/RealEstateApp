#pragma once

#include "RealEstateRepo.h"
#include "OperationStack.h"

typedef struct {

	RealEstateRepo* repo;
	OperationsStack* undoStack;

}Controller;

Controller* createController();
void deleteController(Controller*);

int addRealEstateCtrl(Controller*, const char*, float, float, RealEstateType);
void removeRealEstateCtrl(Controller*, const char*);
RealEstateRepo* getRealEstatesByAddress(Controller*, const char*);
RealEstateRepo* getRealEstatesByType(Controller*, RealEstateType);

RealEstateRepo* getRealEstateRepo(Controller*);

// ====== TEST ===================================

void testController();