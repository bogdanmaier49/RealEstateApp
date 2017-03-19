#include <stdio.h>

#include"DArray.h"
#include "RealEstateRepo.h"
#include "UI.h"

int main()
{
	testDArray();
	testRealEstateRepo();
	testController();

	Controller* c = createController();

	addRealEstateCtrl(c, "Address1", 40.0,	30000.0, APARTMENT);
	addRealEstateCtrl(c, "Address2", 60.0,	780000.77, HOUSE);
	addRealEstateCtrl(c, "Address3", 20.0,	10000.0, APARTMENT);
	addRealEstateCtrl(c, "Address4", 140.0, 23400.23, APARTMENT);
	addRealEstateCtrl(c, "Alta1",	290.0, 9000.0, HOUSE);
	addRealEstateCtrl(c, "Alta2",	154.0, 30050.10, APARTMENT);
	addRealEstateCtrl(c, "Alta3",	80.0,	90546.0, PENTHOUSE);
	addRealEstateCtrl(c, "Alta4",	200.0, 55430.0, PENTHOUSE);
	addRealEstateCtrl(c, "Alta5",	78.0,	88320.50, APARTMENT);

	UI* ui = createUI(c);

	start(ui);

	deleteUI(ui);

	return 0;
}