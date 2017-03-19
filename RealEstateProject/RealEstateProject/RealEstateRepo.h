#pragma once

#include "DArray.h"
#include "RealEstate.h"

#define DEFAULT_REPO_SIZE 32

typedef struct {

	DArray* realEstates;

}RealEstateRepo;

RealEstateRepo* createRealEstateRepo();
void deleteRealEstateRepo(RealEstateRepo*);

int addRealEstate(RealEstateRepo*, RealEstate*);
void removeRealEstate(RealEstateRepo*, RealEstate*);

RealEstate* getRealEstateOnPos(RealEstateRepo*, int);

int getRealEstateRepoLength(RealEstateRepo*);
int findRealEstate(RealEstateRepo*, RealEstate*);

void sortByPrice(RealEstateRepo*);

// ========= RealEstateRepo test ==========================

void testRealEstateRepo();
