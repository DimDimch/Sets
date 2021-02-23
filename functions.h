#pragma once
#include "set.h"
#include "setErrors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define	FALSE 0
#define	TRUE 1

int StopFunction(void);
void HelpFunction(void);
set_t* FindPlenty(char* name);

set_t* CreatePlenty(char* name);
int DestroyPlenty(char* name);

int IsIncludedInPlenty(set_t* A, data_t item);
int AddIntoPlenty(set_t* A, char* tempItem);
int DeleteFromPlenty(set_t* A, data_t item);
long PowerOfPlenty(set_t* A);

set_t* DiffPlenties(set_t* A, set_t* B);
set_t* SimmetricDiff(set_t* A, set_t* B);
set_t* IntersectionOfPlenties(set_t* A, set_t* B);
int IsOneContainOther(set_t* A, set_t* B);
set_t* Union(set_t* A, set_t* B);

int ShowListOfPlenties(void);
int ShowListOfElements(set_t* A);

