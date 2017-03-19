#include "UI.h"

UI* createUI(Controller* ctrl) {
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->controller = ctrl;
	return ui;
}
void deleteUI(UI* ui) {
	deleteController(ui->controller);
	free(ui);
}

void start(UI* ui) {
	while (1)
	{
		printControllerStats(ui);
		printMainMenu(ui);

		printf("\n");
		int command = readIntegerNumber("command: ");
		
		switch (command)
		{
		case 1:
			addRealEstateMenu(ui);
			break;
		case 2:
			removeRealEstateMenu(ui);
			break;
		case 3:
			printRealEstatesByAddress(ui);
			system("PAUSE");
			break;
		case 4:
			printRealEstatesByType(ui);
			system("PAUSE");
			break;
		case 5:
			undo();
			break;
		case 0:
			return;
			break;
		default:
			printf("Unknown command!");
			break;
		}

		clearScreen();
	}
}
void printMainMenu(UI* ui) {
	printf("\n1 - Add new real estate.");
	printf("\n2 - Remove real estate.");
	printf("\n3 - Print real estates by address (ordered by price).");
	printf("\n4 - Print real estates with a given type,\n having the surface greater than a given value.\n");
	printf("\n5 - Undo.");
	printf("\n6 - Redo.");
	printf("\n0 - Exit.");
}

void printControllerStats(UI* ui) {
	printf("Repo - elem: %d / %d \n", 
		getRealEstateRepoLength(getRealEstateRepo(ui->controller)), 
		getMaxLength(getRealEstateRepo(ui->controller)->realEstates)
	);
}

void addRealEstateMenu(UI* ui) {

	printf("Add real estate: \n");
	char address[50];
	printf("Address: ");
	scanf("%s", &address);
	float surface = readFloatNumber("Surface: ");
	float price = readFloatNumber("Price: ");
	RealEstateType type = readRealEstateType("Type: ");

	addRealEstateCtrl(ui->controller, address, surface, price, type);
}

void removeRealEstateMenu(UI* ui) {
	printf("Remove real estate: \n");
	char address[50];
	printf("Address: ");
	scanf("%s", &address);
	removeRealEstateCtrl(ui->controller, address);
}

void printRealEstatesByAddress(UI* ui) {
	
	char address[50];
	printf("Address: ");
	scanf("%s", &address);
	RealEstateRepo* repo = getRealEstatesByAddress(ui->controller, address);
	if (getRealEstateRepoLength(repo) > 0) {
		sortByPrice(repo);
		printRealEstateRepository(repo);
	}
	else {
		sortByPrice(ui->controller->repo);
		printRealEstateRepository(ui->controller->repo);
	}
	deleteRealEstate(repo);
}

void printRealEstatesByType(UI* ui) {
	printf("Print real estates with a given type,\n having the surface greater than a given value\n");
	RealEstateType type = readRealEstateType("Type: ");
	float surface = readFloatNumber("Surface: ");

	RealEstateRepo* repo = getRealEstatesByType(ui->controller, type);

	
	for (int i = 0; i < getRealEstateRepoLength(repo); i++)
	{
		RealEstate *e = getRealEstateOnPos(repo, i);
		if (e->surface < surface)
			removeRealEstate(repo, e);
		deleteRealEstate(e);
	}
	

	printRealEstateRepository(repo);
	deleteRealEstateRepo(repo);
}

void printRealEstateRepository(RealEstateRepo* repo) {
	for (int i = 0; i < getRealEstateRepoLength(repo); i++)
	{
		RealEstate *e = getRealEstateOnPos(repo, i);
		printRealEstate(e);
	}
}

void printRealEstate(RealEstate* e) {
	printf("\n Address: %s, Surface: %f, Price: %f, Type: ", e->address, e->surface, e->price );
	printRealEstateType(e->type);
	printf("\n");
}

void printRealEstateType(RealEstateType type) {
	if (type == HOUSE)
		printf("HOUSE");
	else if (type == APARTMENT)
		printf("APARTMENT");
	else
		printf("PENTHOUSE");
}

int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);

		r = sscanf(s, "%d", &res);
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

RealEstateType readRealEstateType(const char* message) 
{
	printf(message);
	char str[12];
	scanf("%s", &str);
	if (strcmp(str, "HOUSE") == 0)
		return HOUSE;
	else
		if (strcmp(str, "APARTMENT") == 0)
			return APARTMENT;
	
	return PENTHOUSE;
}

float readFloatNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);

		r = sscanf(s, "%f", &res);
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}


void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	int size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}


void clearScreen() {
	system("@cls||clear");
}