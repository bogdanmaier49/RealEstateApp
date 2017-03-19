#include "DArray.h"

DArray* createDArray(int maxLength) {
	DArray* newArray = (DArray*)malloc(sizeof(DArray));

	if (newArray == NULL)
		return NULL;

	newArray->arr = (TElement*)malloc(sizeof(TElement) * maxLength);
	newArray->length = 0;
	newArray->maxLength = maxLength;

	return newArray;
}
void deleteDArray(DArray* arr) {
	if (arr == NULL)
		return;

	free(arr->arr);
	free(arr);
}

void reallocate(DArray* arr, int newSize) {
	if (arr == NULL)
		return;
	if (newSize <= arr->maxLength)
		return;

	arr->arr = (TElement*)realloc(arr->arr, sizeof(TElement) * newSize);
	arr->maxLength = newSize;
}

void addElement(DArray* arr, TElement elem) {
	if (arr == NULL || elem == NULL)
		return;

	if (arr->length >= arr->maxLength)
		reallocate(arr, arr->length + 1);

	arr->arr[arr->length] = elem;
	arr->length++;
}

void deleteElement(DArray* arr, int pos) {
	if (arr == NULL)
		return;

	if (pos < 0 || pos >= arr->length)
		return;

	for (int i = pos; i < arr->length; i++)
		arr->arr[i] = arr->arr[i + 1];

	arr->length--;
}

TElement get(DArray* arr, int pos) {
	if (pos < 0 || pos >= arr->length)
		return NULL;

	if (arr == NULL)
		return;

	return arr->arr[pos];
}
int getLength(DArray* arr) {
	if (arr == NULL)
		return -1;
	return arr->length;
}
int getMaxLength(DArray* arr) {
	if (arr == NULL)
		return -1;
	return arr->maxLength;
}

void interchange(DArray* arr, int i, int j) {
	TElement aux = arr->arr[i];
	arr->arr[i] = arr->arr[j];
	arr->arr[j] = aux;
}

// ========= DArray test ===================================

void testDArray() {
	DArray* darray = createDArray(2);
	assert(getMaxLength(darray) == 2);
	assert(getLength(darray) == 0);

	RealEstate *house1 = createRealEstate("Adress1", 53.2, 1000.49, APARTMENT);
	RealEstate *house2 = createRealEstate("Adress2", 45.2, 2000.49, PENTHOUSE);
	RealEstate *house3 = createRealEstate("Adress3", 103.2, 4500.49, HOUSE);


	addElement(darray, house1);
	assert(getLength(darray) == 1);

	addElement(darray, house2);
	addElement(darray, house3);
	assert(getLength(darray) == 3);

	deleteElement(darray, 1);
	assert(getLength(darray) == 2);


	testRealEstate(get(darray, 0), "Adress1", 53.2, 1000.49, APARTMENT);
	testRealEstate(get(darray, 1), "Adress3", 103.2, 4500.49, HOUSE);

	deleteDArray(darray);

}

void testRealEstate(RealEstate *e, const char* adr, float surface, float price, RealEstateType type) {
	assert(strcmp(getRealEstateAddress(e), adr) == 0);
	assert(e->surface == surface);
	assert(e->price == price);
	assert(e->type == type);
}