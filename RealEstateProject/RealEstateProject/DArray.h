#pragma once

#include "RealEstate.h"
#include <assert.h>
#include <string.h>

typedef RealEstate* TElement;

typedef struct {

	TElement* arr;
	int length;
	int maxLength;

}DArray;

DArray* createDArray(int maxLength);
void deleteDArray(DArray* arr);

void reallocate(DArray* arr, int newSize);

void addElement(DArray* arr, TElement elem);
void deleteElement(DArray* arr, int pos);

TElement get(DArray* arr, int pos);
int getLength(DArray* arr);
int getMaxLength(DArray* arr);

void interchange(DArray*, int i, int j);

// ========= DArray test ===================================

void testDArray();
void testRealEstate(RealEstate *e, const char*, float, float, RealEstateType);