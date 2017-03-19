#pragma once

#include "Controller.h"
#include <stdlib.h>

typedef struct {

	Controller* controller;

} UI;

UI* createUI(Controller*);
void deleteUI(UI*);

void start(UI*);
void printMainMenu(UI*);
void printControllerStats(UI*);

void addRealEstateMenu(UI*);
void removeRealEstateMenu(UI*);
void printRealEstatesByAddress(UI*);
void printRealEstateRepository(RealEstateRepo*);
void printRealEstate(RealEstate* );
void printRealEstateType(RealEstateType );
void printRealEstatesByType(UI*);

int readIntegerNumber(const char* message);
float readFloatNumber(const char* message);
RealEstateType readRealEstateType(const char* message);
void readStringWithSpaces(const char* message, int maxStrSize, char str[]);

void clearScreen();