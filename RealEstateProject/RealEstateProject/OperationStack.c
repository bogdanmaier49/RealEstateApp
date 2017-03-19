#include "OperationStack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Operation* createOperation(RealEstate* e, char* operationType)
{
	Operation* o = (Operation*)malloc(sizeof(Operation));
	o->realEstate = copyRealEstate(e);

	if (operationType != NULL)
	{
		o->operationType = (char*)malloc(sizeof(strlen(operationType) + 1));
		strcpy(o->operationType, operationType);
	}
	else
		o->operationType = NULL;

	return o;
}

void deleteOperation(Operation* o)
{
	if (o == NULL)
		return;

	deleteRealEstate(o->realEstate);
	free(o->operationType);
	free(o);
}

Operation* copyOperation(Operation * o)
{
	if (o == NULL)
		return NULL;

	Operation* newOp = createOperation(o->realEstate, o->operationType);
	return newOp;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

RealEstate* getRealEstate(Operation* o)
{
	return o->realEstate;
}

// ---------------------------------------------------------------

OperationsStack* createStack()
{
	OperationsStack* s = (OperationsStack*)malloc(sizeof(OperationsStack));
	s->length = 0;

	return s;
}

void deleteStack(OperationsStack* s)
{
	if (s == NULL)
		return;

	for (int i = 0; i < s->length; i++)
		deleteOperation(s->operations[i]);

	free(s);
}

void push(OperationsStack* s, Operation* o)
{
	if (isFull(s))
		return;

	s->operations[s->length++] = copyOperation(o);	
}

Operation* pop(OperationsStack* s)
{
	if (isEmpty(s))
		return NULL;

	s->length--;
	return s->operations[s->length];
}

int isEmpty(OperationsStack* s)
{
	if (s->length == 0)
		return 1;
	return 0;
}

int isFull(OperationsStack* s)
{
	return s->length == 100;
}


void testsStack()
{
	OperationsStack* s = createStack();

	RealEstate *e1 = createRealEstate("Adress1", 53.2, 1000.49, APARTMENT);
	RealEstate *e2 = createRealEstate("Adress2", 45.2, 2000.49, PENTHOUSE);

	Operation* o1 = createOperation(e1, "add");
	Operation* o2 = createOperation(e2, "add");
	Operation* o3 = createOperation(e1, "remove");

	deleteRealEstate(e1);
	deleteRealEstate(e2);

	push(s, o1);
	push(s, o2);
	push(s, o3);

	deleteOperation(o1);
	deleteOperation(o2);
	deleteOperation(o3);

	assert(isFull(&s) == 0);
	assert(isEmpty(&s) == 0);
	Operation* o = pop(s);
	assert(strcmp(o->operationType, "remove") == 0);
	deleteOperation(o);

	o = pop(s);
	assert(strcmp(o->operationType, "add") == 0);
	deleteOperation(o);

	o = pop(s);
	assert(strcmp(o->operationType, "add") == 0);
	deleteOperation(o);

	assert(isEmpty(s) == 1);
	
	deleteStack(s);
}