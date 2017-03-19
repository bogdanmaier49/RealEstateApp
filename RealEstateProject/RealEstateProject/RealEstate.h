#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef enum {
	HOUSE,
	APARTMENT,
	PENTHOUSE

} RealEstateType;

typedef struct {
	const char*		address;
	float			surface;
	float			price;
	RealEstateType	type;
} RealEstate;

RealEstate* createRealEstate(const char*, float, float, RealEstateType);
void deleteRealEstate(RealEstate* e);

const char* getRealEstateAddress(RealEstate* e);
float getRealEstateSurface(RealEstate* e);
float getRealEstatePrice(RealEstate* e);
RealEstateType getRealEstateType(RealEstate* e);

RealEstate* copyRealEstate(RealEstate* e);