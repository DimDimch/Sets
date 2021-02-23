#include "set.h"
#include <windows.h>
#include <stdio.h>
#include "setErrors.h"
#include "engine.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC


int main(void) {
	//window
	HWND hwnd;
	char Title[1024];
	GetConsoleTitle(Title, 1024);
	hwnd = FindWindow(NULL, Title);
	MoveWindow(hwnd, 0, 0, 600, 600, TRUE);
	system("title A package for working with sets");
	system("color F0");
	printf("----------------------------------------------\n");
	printf("<help> (or just <h>) to get a list of commands\n");
	printf("<stop> (or just <s>) to end the program\n");
	printf("----------------------------------------------\n");
	
	//main part
	char strReport[PLENTY_MAX_REPORT_LEN] = {0};
	int stopCheck = 0;
	do {
		fgets(strReport, PLENTY_MAX_REPORT_LEN, stdin);
		strReport[strlen(strReport) - 1] = 0;
		stopCheck = BrainFunc(strReport);
	} while (stopCheck != 1);
	
	//leaks
	printf("\n\n----------------------------------------------\n");
	printf("Memory leaks: \n");
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	printf("----------------------------------------------\n");
	return 0;
}