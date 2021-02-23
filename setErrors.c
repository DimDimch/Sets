#include "setErrors.h"
#include <stdio.h>

static void ErrorsPrint(int number) {
	char a_err[][60] = {
		"the entered element is already contained in this set",    //1
		"this element does not exist in this set",                 //2 
		"something bad...",                                        //3
		"set with this name already exists",                       //4
		"empty string",                                            //5
		"incorrect count of operands",                             //6
		"set or element not found",                                //7
		"unknown command",                                         //8
		"invalid command",                                         //9
		"unresolved values are used",                              //10
		"the command or operand exceeds the allowed length",       //11
	};
	printf("ERROR: %s\n", a_err[number - 1]);
}
void ErrorsFunc(int number) {
	switch (number) {
	case 1: ErrorsPrint(1);
		break;
	case 2: ErrorsPrint(2);
		break;
	case 3: ErrorsPrint(3);
		break;
	case 4: ErrorsPrint(4);
		break;
	case 5: ErrorsPrint(5);
		break;
	case 6: ErrorsPrint(6);
		break;
	case 7: ErrorsPrint(7);
		break;
	case 8: ErrorsPrint(8);
		break;
	case 9: ErrorsPrint(9);
		break;
	case 10: ErrorsPrint(10);
		break;
	case 11: ErrorsPrint(11);
		break;
	}
}