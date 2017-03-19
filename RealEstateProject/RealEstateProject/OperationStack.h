#pragma once
#include "RealEstate.h"
#include "DArray.h"
#include <string.h>

typedef struct
{
	RealEstate* realEstate;
	char* operationType;
} Operation;

Operation* createOperation(RealEstate* p, char* operationType);
void deleteOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
RealEstate* getRealEstate(Operation* o);

// ---------------------------------------------------------------
typedef struct
{
	Operation* operations[100];
	int length;
} OperationsStack;

OperationsStack* createStack();
void deleteStack(OperationsStack* s);
void push(OperationsStack* s, Operation* o);
Operation* pop(OperationsStack* s);
int isEmpty(OperationsStack* s);
int isFull(OperationsStack* s);

void testsStack();