#include "RealEstate.h"

RealEstate* createRealEstate(const char* address, float surface, float price, RealEstateType type){
	RealEstate* e = (RealEstate*)malloc(sizeof(RealEstate));

	if (e == NULL)
		return NULL;

	e->address = (const char*)malloc(strlen(address) * sizeof(char) + 1);
	strcpy(e->address, address);
	e->surface = surface;
	e->price = price;
	e->type = type;
	
	return e;
}

void deleteRealEstate(RealEstate* e) {
	if (e == NULL)
		return;

	free(e->address);
	free(e);
}

RealEstate* copyRealEstate(RealEstate* e){
	if (e == NULL)
		return NULL;

	RealEstate* newRealEstate = createRealEstate(e->address, e->surface, e->price, e->type);
	return newRealEstate;
}


// ========== Getters ==========================================================

const char* getRealEstateAddress(RealEstate* e) {
	if (e == NULL)
		return;
	
	return e->address;
}

float getRealEstateSurface(RealEstate* e) {
	if (e == NULL)
		return;

	return e->surface;
}

float getRealEstatePrice(RealEstate* e) {
	if (e == NULL)
		return;

	return e->price;
}

RealEstateType getRealEstateType(RealEstate* e) {
	if (e == NULL)
		return;

	return e->type;
}
