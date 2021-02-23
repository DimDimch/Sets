#include "engine.h"
#include "functions.h"
#include "setErrors.h"
#pragma warning(disable:4996)

static int GetTokens(const char* str, report_t* report) {
	if (str[0] == 0) {
		ErrorsFunc(5);
		return -1;
	}

	int i = 0, k = 0;
	//command
	do {
		if (!RANGE_OF_VALUES(str[i])) {
			ErrorsFunc(10);
			return -1;
		}
		if (k >= PLENTY_MAX_COMMAND_LEN) {
			ErrorsFunc(11);
			return -1;
		}
		report->commandName[k] = str[i];
		++k;
		++i;
	} while (str[i] != ' ' && str[i] != 0);
	report->commandName[k] = 0;

	//is it all?
	while (str[++i] == ' ');
	if (str[i] == 0) {
		report->operand1[0] = 0;
		report->operand2[0] = 0;
		return 0;
	}

	//operand 1
	if (str[i] == '"') {
		k = 0;
		++i;
		do {
			if (!RANGE_OF_VALUES(str[i])) {
				ErrorsFunc(10);
				return -1;
			}
			if (k >= PLENTY_MAX_ITEM_LEN) {
				ErrorsFunc(11);
				return -1;
			}
			report->operand1[k] = str[i];
			++k;
			++i;
		} while (str[i] != '"' && str[i] != 0);
		if (str[i] != '"') {
			ErrorsFunc(9);
			return -1;
		}
		else
			i++;

		while (isspace(str[i])) {
			i++;
		}
		if (str[i] == 0) {
			report->operand1[k] = 0;
			report->operand2[0] = 0;
			return 1;
		}
	}
	else {
		k = 0;
		do {
			if (!RANGE_OF_VALUES(str[i])) {
				ErrorsFunc(10);
				return -1;
			}
			if (k >= PLENTY_MAX_ITEM_LEN) {
				ErrorsFunc(11);
				return -1;
			}
			report->operand1[k] = str[i];
			k++;
			i++;
		} while (str[i] != ' ' && str[i] != 0);
		while (isspace(str[i])) {
			i++;
		}
		if (str[i] == 0) {
			report->operand1[k] = 0;
			report->operand2[0] = 0;
			return 1;
		}
	}
	report->operand1[k] = 0;

	//operand 2
	if (str[i] == '"') {
		k = 0;
		i++;
		do {
			if (!RANGE_OF_VALUES(str[i])) {
				ErrorsFunc(10);
				return -1;
			}
			if (k >= PLENTY_MAX_ITEM_LEN) {
				ErrorsFunc(11);
				return -1;
			}
			report->operand2[k] = str[i];
			k++;
			i++;
		} while (str[i] != '"' && str[i] != 0);
		if (str[i] != '"') {
			ErrorsFunc(9);
			return -1;
		}
		else
			i++;

		while (isspace(str[i])) {
			i++;
		}
		if (str[i] == 0) {
			report->operand2[k] = 0;
			return 2;
		}
	}
	else {
		k = 0;
		do {
			if (!RANGE_OF_VALUES(str[i])) {
				ErrorsFunc(10);
				return -1;
			}
			if (k >= PLENTY_MAX_ITEM_LEN) {
				ErrorsFunc(11);
				return -1;
			}
			report->operand2[k] = str[i];
			k++;
			i++;
		} while (str[i] != ' ' && str[i] != 0);
		while (isspace(str[i])) {
			i++;
		}
		if (str[i] == 0) {
			report->operand2[k] = 0;
			return 2;
		}
		else {
			ErrorsFunc(6);
			return -1;
		}
	}
	return -1;
}
static void CopyIntoClipboard(const char* data) {
	FILE* fpBuffer;
	fpBuffer = fopen("__SET_SERDYUKOV_HELPFILE__.txt", "w");
	if (fpBuffer != NULL) {
		fprintf(fpBuffer, "%s", data);
		fclose(fpBuffer);
		system("clip < __SET_SERDYUKOV_HELPFILE__.txt");
		remove("__SET_SERDYUKOV_HELPFILE__.txt");
	}
}

int BrainFunc(char* str) {
	if (str == NULL) {
		ErrorsFunc(3);
		return -1;
	}
	int countOperands = 0, check = 0;
	set_t* checkPlenty = NULL;

	char* buffer[30] = { 0 };


	report_t report = { {0},{0},{0} };
	countOperands = GetTokens(str, &report);
	if (countOperands == -1)
		return -1;

	//which command?
	switch (report.commandName[0]) {
	case 'c': //<create>
		if (strcmp(report.commandName, "create") == 0 || strcmp(report.commandName, "CREATE") == 0) {
			if (countOperands != 1) {
				ErrorsFunc(6);
				return -1;
			}
			checkPlenty = CreatePlenty(report.operand1);
			if (checkPlenty == NULL)
				ErrorsFunc(4);
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'd': //<destroy>, <del>, <diff>
		if (strcmp(report.commandName, "destroy") == 0 || strcmp(report.commandName, "DESTROY") == 0) {
			if (countOperands != 1) {
				ErrorsFunc(6);
				return -1;
			}
			check = DestroyPlenty(report.operand1);
			if (check != TRUE)
				ErrorsFunc(7);
			break;
		}
		if (strcmp(report.commandName, "del") == 0 || strcmp(report.commandName, "DEL") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			check = DeleteFromPlenty(FindPlenty(report.operand1), (data_t)report.operand2);
			if (check != TRUE)
				ErrorsFunc(7);
			break;
		}
		if (strcmp(report.commandName, "diff") == 0 || strcmp(report.commandName, "DIFF") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			checkPlenty = DiffPlenties(FindPlenty(report.operand1), FindPlenty(report.operand2));
			if (checkPlenty == NULL) {
				ErrorsFunc(7);
				return -1;
			}
			else {
				ShowListOfElements(checkPlenty);
				CopyIntoClipboard(checkPlenty->name);
				printf("*The name of the result set is copied to the clipboard\n");
			}
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'p': //<power>
		if (strcmp(report.commandName, "power") == 0 || strcmp(report.commandName, "POWER") == 0) {
			if (countOperands != 1) {
				ErrorsFunc(6);
				return -1;
			}
			check = PowerOfPlenty(FindPlenty(report.operand1));
			if (check != 0)
				ErrorsFunc(7);
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'a': //<add>
		if (strcmp(report.commandName, "add") == 0 || strcmp(report.commandName, "ADD") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			check = AddIntoPlenty(FindPlenty(report.operand1), (data_t)report.operand2);
			if (check == -1)
				ErrorsFunc(7);
			if (check == FALSE)
				ErrorsFunc(1);
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'i': //<isinclude>, <inter>, <iscontain>
		if (strcmp(report.commandName, "isinclude") == 0 || strcmp(report.commandName, "ISINCLUDE") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			check = IsIncludedInPlenty(FindPlenty(report.operand1), (data_t)report.operand2);
			if (check == TRUE)
				printf("Yes\n");
			else if (check == FALSE)
				printf("No\n");
			else
				ErrorsFunc(7);
			break;
		}
		if (strcmp(report.commandName, "inter") == 0 || strcmp(report.commandName, "INTER") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			checkPlenty = IntersectionOfPlenties(FindPlenty(report.operand1), FindPlenty(report.operand2));
			if (checkPlenty == NULL) {
				ErrorsFunc(7);
				return -1;
			}
			else {
				ShowListOfElements(checkPlenty);
				CopyIntoClipboard(checkPlenty->name);
				printf("*The name of the result set is copied to the clipboard\n");
			}
			break;
		}
		if (strcmp(report.commandName, "iscontain") == 0 || strcmp(report.commandName, "ISCONTAIN") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			check = IsOneContainOther(FindPlenty(report.operand1), FindPlenty(report.operand2));
			if (check == TRUE)
				printf("Yes\n");
			else if (check == FALSE)
				printf("No\n");
			else
				ErrorsFunc(7);
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'u': //<union>
		if (strcmp(report.commandName, "union") == 0 || strcmp(report.commandName, "UNION") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			checkPlenty = Union(FindPlenty(report.operand1), FindPlenty(report.operand2));
			if (checkPlenty == NULL) {
				ErrorsFunc(7);
				return -1;
			}
			else {
				ShowListOfElements(checkPlenty);
				CopyIntoClipboard(checkPlenty->name);
				printf("*The name of the result set is copied to the clipboard\n");
			}
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 's': //<sdiff>, <stop>
		if (strcmp(report.commandName, "sdiff") == 0 || strcmp(report.commandName, "sdiff") == 0) {
			if (countOperands != 2) {
				ErrorsFunc(6);
				return -1;
			}
			checkPlenty = SimmetricDiff(FindPlenty(report.operand1), FindPlenty(report.operand2));
			if (checkPlenty == NULL) {
				ErrorsFunc(7);
				return -1;
			}
			else {
				ShowListOfElements(checkPlenty);
				CopyIntoClipboard(checkPlenty->name);
				printf("*The name of the result set is copied to the clipboard\n");
			}
			break;
		}
		if (strcmp(report.commandName, "s") == 0 || strcmp(report.commandName, "stop") == 0 || strcmp(report.commandName, "STOP") == 0) {
			if (countOperands != 0) {
				ErrorsFunc(6);
				return -1;
			}
			StopFunction();
			return 1; //one place, where return -1
		}
		ErrorsFunc(8);
		return -1;
	case 'l': //<list>
		if (strcmp(report.commandName, "list") == 0 || strcmp(report.commandName, "LIST") == 0) {
			if (countOperands != 0) {
				ErrorsFunc(6);
				return -1;
			}
			ShowListOfPlenties();
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'e': //<elements>
		if (strcmp(report.commandName, "elem") == 0 || strcmp(report.commandName, "ELEM") == 0) {
			if (countOperands != 1) {
				ErrorsFunc(6);
				return -1;
			}
			check = ShowListOfElements(FindPlenty(report.operand1));
			if (check != 0)
				ErrorsFunc(7);
			break;
		}
		ErrorsFunc(8);
		return -1;
	case 'h': //<help>
		if (strcmp(report.commandName, "h") == 0 || strcmp(report.commandName, "help") == 0 || strcmp(report.commandName, "HELP") == 0) {
			if (countOperands != 0) {
				ErrorsFunc(6);
				return -1;
			}
			HelpFunction();
			break;
		}
		ErrorsFunc(8);
		return -1;
	default:
		ErrorsFunc(8);
		return -1;
	}
	return 0;
}

