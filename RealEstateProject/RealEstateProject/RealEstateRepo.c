#include "RealEstateRepo.h"

RealEstateRepo* createRealEstateRepo() {
	RealEstateRepo* repo = (RealEstateRepo*)malloc(sizeof(RealEstateRepo));
	repo->realEstates = createDArray(DEFAULT_REPO_SIZE);
	return repo;
}
void deleteRealEstateRepo(RealEstateRepo* repo) {
	if (repo == NULL)
		return;

	deleteDArray(repo->realEstates);
	free(repo);
}

int addRealEstate(RealEstateRepo* repo, RealEstate* e) {
	if (repo == NULL || e == NULL)
		return -1;

	if (findRealEstate(repo, e) == -2) {
		addElement(repo->realEstates, e);
		return 1;
	}

	return 0;
}
void removeRealEstate(RealEstateRepo* repo, RealEstate* e) {
	if (repo == NULL || e == NULL)
		return;


	deleteElement(repo->realEstates, findRealEstate(repo, e));

}

RealEstate* getRealEstateOnPos(RealEstateRepo* repo, int pos) {
	if (repo == NULL)
		return NULL;

	return get(repo->realEstates, pos);
}

int getRealEstateRepoLength(RealEstateRepo* repo) {
	if (repo == NULL)
		return -1;

	return getLength(repo->realEstates);
}

int findRealEstate(RealEstateRepo* repo, RealEstate* e) {
	if (repo == NULL || e == NULL)
		return;

	for (int i = 0; i < repo->realEstates->length; i++)
		if (strcmp(getRealEstateAddress(getRealEstateOnPos(repo, i)), getRealEstateAddress(e)) == 0) {
			return i;
		}

	return -2;
}

void sortByPrice(RealEstateRepo* repo) {
	if (repo == NULL)
		return;

	for (int i=0; i<getLength(repo->realEstates); i++)
		for (int j = 0; j < getLength(repo->realEstates); j++) {
			RealEstate* el_i = getRealEstateOnPos(repo, i);
			RealEstate* el_j = getRealEstateOnPos(repo, j);

			if (el_i->price < el_j->price)
				interchange(repo->realEstates, i, j);

			//deleteRealEstate(el_i);
			//deleteRealEstate(el_j);
		}
}


// ========= RealEstateRepo test ==========================

void testRealEstateRepo() {

	RealEstateRepo* repo = createRealEstateRepo();

	assert(getRealEstateRepoLength(repo) == 0);

	RealEstate *house1 = createRealEstate("Adress1", 53.2, 1000.49, APARTMENT);
	RealEstate *house2 = createRealEstate("Adress2", 45.2, 2000.49, PENTHOUSE);
	RealEstate *house3 = createRealEstate("Adress3", 103.2, 4500.49, HOUSE);

	addRealEstate(repo, house1);
	addRealEstate(repo, house2);
	addRealEstate(repo, house2);
	addRealEstate(repo, house3);
	
	assert(getRealEstateRepoLength(repo) == 3);

	removeRealEstate(repo, house2);

	assert(getRealEstateRepoLength(repo) == 2);

	testRealEstate(getRealEstateOnPos(repo, 0), "Adress1", 53.2, 1000.49, APARTMENT);
	testRealEstate(getRealEstateOnPos(repo, 1), "Adress3", 103.2, 4500.49, HOUSE);

	deleteRealEstateRepo(repo);
}