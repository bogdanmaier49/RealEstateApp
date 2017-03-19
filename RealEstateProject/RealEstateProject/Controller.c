#include "Controller.h"


Controller* createController() {
	Controller* c = (Controller*)malloc(sizeof(Controller));
	OperationsStack* stack = createStack();
	c->repo = createRealEstateRepo();
	c->undoStack = stack;
	return c;
}
void deleteController(Controller* ctrl) {
	deleteRealEstateRepo(ctrl->repo);
	deleteStack(ctrl->undoStack);
	free(ctrl);
}

int addRealEstateCtrl(Controller* ctrl, const char* address, float surface, float price, RealEstateType type) {
	if (ctrl == NULL)
		return -3;

	RealEstate* e = createRealEstate(address, surface, price, type);
	int result = addRealEstate(ctrl->repo, e);
	if (result == 1)
	{
		Operation* o = createOperation(e, "add");
		push(ctrl->undoStack, o);
		deleteOperation(o);
	}

	//deleteRealEstate(e);

	return result;
}

void removeRealEstateCtrl(Controller* ctrl, const char* address) {
	for (int i = 0; i < getRealEstateRepoLength(ctrl->repo); i++) {

		RealEstate* e = getRealEstateOnPos(ctrl->repo, i);

		if (strcmp(address, getRealEstateAddress(e)) == 0)
			removeRealEstate(ctrl->repo, e);

	}
}

RealEstateRepo* getRealEstateRepo(Controller* ctrl) {
	if (ctrl == NULL)
		return NULL;

	return ctrl->repo;
}

RealEstateRepo* getRealEstatesByAddress(Controller* ctrl, const char* address) {
	RealEstateRepo* repo = createRealEstateRepo();

	for (int i = 0; i < getRealEstateRepoLength(ctrl->repo); i++) {
		RealEstate* curentRealEstate = getRealEstateOnPos(ctrl->repo, i);
		if (strstr(curentRealEstate->address, address) != NULL) {
			addRealEstate(repo, curentRealEstate);
		}
	}

	return repo;
}

RealEstateRepo* getRealEstatesByType(Controller* ctrl, RealEstateType type) {
	RealEstateRepo* repo = createRealEstateRepo();

	for (int i = 0; i < getRealEstateRepoLength(ctrl->repo); i++) {
		RealEstate* curentRealEstate = getRealEstateOnPos(ctrl->repo, i);
		if (type == curentRealEstate->type) {
			addRealEstate(repo, curentRealEstate);
		}
	}

	return repo;

}

int undo(Controller* ctrl)
{
	if (ctrl == NULL)
		return -1;

	if (isEmpty(ctrl->undoStack))
	{
		return 0;
	}

	Operation* operation = pop(ctrl->undoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		RealEstate* e = getRealEstate(operation);
		deleteRealEstate(e);
	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		RealEstate* e = getRealEstate(operation);
		addRealEstate(ctrl->repo, e);
	}

	deleteOperation(operation);

	return 1;

}

int redo(Controller* ctrl)
{
	if (ctrl == NULL)
		return -1;

	if (isFull(ctrl->undoStack))
	{
		return 0;
	}

	Operation* operation = pop(ctrl->undoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		RealEstate* e = getRealEstate(operation);
		addRealEstate(ctrl->repo, e);
	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		RealEstate* e = getRealEstate(operation);
		deleteRealEstate(e);
	}

	deleteOperation(operation);

	return 1;

}

void testController() {

	Controller* ctrl = createController();

	assert(getRealEstateRepoLength(ctrl->repo) == 0);

	addRealEstateCtrl(ctrl, "Address1", 40.0, 30000.0, APARTMENT);
	addRealEstateCtrl(ctrl, "Address2", 60.0, 780000.77, HOUSE);
	addRealEstateCtrl(ctrl, "Address3", 20.0, 10000.0, APARTMENT);
	addRealEstateCtrl(ctrl, "Address4", 140.0, 23400.23, APARTMENT);
	addRealEstateCtrl(ctrl, "Alta1", 290.0, 9000.0, HOUSE);
	addRealEstateCtrl(ctrl, "Alta2", 154.0, 30050.10, APARTMENT);
	addRealEstateCtrl(ctrl, "Alta3", 80.0, 90546.0, PENTHOUSE);
	addRealEstateCtrl(ctrl, "Alta4", 200.0, 55430.0, PENTHOUSE);
	addRealEstateCtrl(ctrl, "Alta5", 78.0, 88320.50, APARTMENT);

	assert(getRealEstateRepoLength(ctrl->repo) == 9);

	removeRealEstateCtrl(ctrl, "Alta1");
	removeRealEstateCtrl(ctrl, "Alta4");

	assert(getRealEstateRepoLength(ctrl->repo) == 7);

	assert(strcmp(getRealEstateAddress(getRealEstateOnPos(ctrl->repo, 4)), "Alta2") == 0);
	assert(strcmp(getRealEstateAddress(getRealEstateOnPos(ctrl->repo, 6)),"Alta5") == 0);

	deleteController(ctrl);
}


