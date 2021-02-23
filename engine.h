#pragma once
#include "set.h"
#include "setErrors.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char commandName[PLENTY_MAX_COMMAND_LEN];
	char operand1[PLENTY_MAX_ITEM_LEN];
	char operand2[PLENTY_MAX_ITEM_LEN];
}report_t;

int BrainFunc(char* str);