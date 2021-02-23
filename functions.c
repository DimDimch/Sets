#include "functions.h"
#include <locale.h>
#pragma warning(disable:4996)

setList_t listOfSets = { NULL };
struct {
	int Union;
	int Inter;
	int Diff;
	int SDiff;
}countOfCalls = { 1,1,1,1 };

//SYSTEM FUNCTIONS
int StopFunction(void) {
	set_t* p = listOfSets.head, * t;
	while (p != NULL) {
		t = p->next;
		FreePlenty(p);
		p = t;
	}
	printf("\nThe program is finished successfully!\n");
	return 0;
}
void HelpFunction(void) {
	setlocale(LC_ALL, "Russian");
	printf("----------------------------------------------\n");
	printf("*—интаксис: <command> \"<op1>\" \"<op2>\"\n");
	printf("CREATE - создание множества\n     (например: create \"A\")\n");
	printf("DESTROY - удаление множества\n     (например: destroy \"A\")\n");
	printf("POWER - можность множества\n     (например: power \"A\")\n");
	printf("ADD - добавление эл-та в мн-во\n     (например: add \"A\" \"a\")\n");
	printf("DEL - удаление эл-та из мн-ва\n     (например: del \"A\" \"a\")\n");
	printf("ISINCLUDE - проверка принадлежности эл-та мн-ву\n     (например: isinclude \"A\" \"a\")\n");
	printf("UNION - объединение множеств\n     (например: union \"A\" \"B\")\n");
	printf("INTER - пересечение множеств\n     (например: inter \"A\" \"B\")\n");
	printf("DIFF - разность множеств\n     (например: diff \"A\" \"B\")\n");
	printf("SDIFF - симметрическа€ разность\n     (например: sdiff \"A\" \"B\")\n");
	printf("ISCONTAIN - проверка включени€ мн-ва ј в мн-во ¬\n     (например: iscontain \"A\" \"B\")\n");
	printf("LIST - просмотр существующих множеств\n     (например: list\n");
	printf("ELEM - просмотр элементов множества\n     (например: elem \"A\")\n");
	printf("STOP - останавливает работу программы\n");
	printf("----------------------------------------------\n");
}

//HELPFUL FUNCTIONS
void PrintPlenty(set_t* A) {
	if (A == NULL)
		return;

	printf("\"%s\": ", A->name);
	if (A->head == NULL) {
		printf("{ - }");
		return;
	}
	node_t* p = A->head;
	printf("{ ");
	while (p != NULL) {
		printf("%c%s%c ", '"', p->data, '"');
		p = p->next;
	}
	printf("}\n");
}
set_t* FindPlenty(char* name) {
	if (name == NULL)
		return NULL;

	set_t* p = listOfSets.head;
	if (p == NULL)
		return NULL;
	while (p != NULL) {
		if (strcmp(p->name, name) == 0)
			return p;
		else
			p = p->next;
	}
	return NULL;
}

//CREATE AND DELETE FUNCTIONS
set_t* CreatePlenty(char* name) {
	set_t* A = (set_t*)malloc(sizeof(set_t)), *p = listOfSets.head, *t = NULL, *prev = NULL;
	if (A == NULL) 
		return NULL;

	if (FindPlenty(name) != NULL) {
		free(A);
		return NULL;
	}

	char* tempName = malloc(strlen(name) + 1);
	if (tempName == NULL) {
		free(A);
		return NULL;
	}
	strcpy(tempName, name);
	A->name = tempName;
	A->head = NULL;
	A->next = NULL;

	if (p == NULL) {
		listOfSets.head = A;
		A->next = NULL;
		return A;
	}
	else {
		while (p->next != NULL && strcmp(p->name, name) < 0) {
			prev = p;
			p = p->next;
		}
		if (p->next != NULL) {
			t = p->next;
			if (prev != NULL) {
				prev->next = A;
				A->next = p;
				p->next = t;
			}
			else {
				listOfSets.head = A;
				A->next = p;
			}
		}
		else {
			if (strcmp(p->name, name) < 0) {
				t = p->next;
				p->next = A;
				A->next = t;
			}
			else {
				if (prev != NULL) {
					prev->next = A;
					A->next = p;
				}
				else {
					listOfSets.head = A;
					A->next = p;
				}
			}
		}
	}
	return A;
}
static int FreePlenty(set_t* A) {
	if (A == NULL)
		return FALSE;

	if (A->head == NULL) {
		free(A->name);
		free(A);
		return TRUE;
	}

	node_t* p = A->head, * t;
	do {
		t = p->next;
		if (p->data != NULL)
			free(p->data);
		free(p);
		p = t;
	} while (t != NULL);
	free(A->name);
	free(A);
	return TRUE;
}
int DestroyPlenty(char* name) {
	if (name == NULL)
		return FALSE;

	set_t* p = listOfSets.head, *prev = NULL;
	if (p == NULL)
		return FALSE;

	while (p != NULL) {
		if (strcmp(p->name, name) == 0) {
			if (prev == NULL) {
				listOfSets.head = p->next;
			}
			else 
				prev->next = p->next;
			FreePlenty(p);
			p = NULL;
			return TRUE;
		}
		prev = p;
		p = p->next;
	}
	return FALSE;
}

//SIMPLE OPERATIONS
int IsIncludedInPlenty(set_t* A, data_t item) {
	if (A == NULL)
		return -1;
	if (A->head == NULL) {
		return FALSE;
	}
	node_t* p = A->head;
	do {
		if (strcmp(p->data, item) == 0)
			return TRUE;
		p = p->next;
	} while (p != NULL);
	return FALSE;
}
int AddIntoPlenty(set_t* A, char* tempItem) {
	if (A == NULL || tempItem == NULL)
		return -1;

	if (IsIncludedInPlenty(A, tempItem) == TRUE) {
		return FALSE;
	}

	data_t item = malloc(strlen(tempItem) + 1);
	node_t* p = A->head, *prev = NULL, *t = NULL, *newElem = (node_t*)malloc(sizeof(node_t));
	if (newElem == NULL || item == NULL) {
		if (newElem != NULL)
			free(newElem);
		if (item != NULL)
			free(item);
		return -1;
	}

	strcpy(item, tempItem);
	newElem->next = NULL;
	newElem->data = item;
	
	//if one element
	if (A->head == NULL) {
		A->head = newElem;
		return TRUE;
	}
	else {
		while (p->next != NULL && strcmp(p->data, item) < 0) {
			prev = p;
			p = p->next;
		}
		if (p->next != NULL) {
			t = p->next;
			if (prev != NULL) {
				prev->next = newElem;
				newElem->next = p;
				p->next = t;
			}
			else {
				A->head = newElem;
				newElem->next = p;
			}
		}
		else {
			if (strcmp(p->data, item) < 0) {
				t = p->next;
				p->next = newElem;
				newElem->next = t;
			}
			else {
				if (prev != NULL) {
					prev->next = newElem;
					newElem->next = p;
				}
				else {
					A->head = newElem;
					newElem->next = p;
				}
			}
		}
	}

}
int DeleteFromPlenty(set_t* A, data_t item) {
	if (A == NULL || A->head == NULL || item == NULL)
		return -1;

	node_t* p = A->head, *t, *prev;

	//if it is first elem
	if (A->head->data != NULL && strcmp(A->head->data, item) == 0) {
		free(A->head->data);
		if (A->head->next == NULL) {
			free(A->head);
			A->head = NULL;
			return TRUE;
		}
		else {
			t = A->head->next;
			free(A->head);
			A->head = t;
			return TRUE;
		}
	}

	//if not first
	do {
		if (strcmp(p->next->data, item) == 0) {
			free(p->next->data);
			t = p->next->next;
			free(p->next);
			p->next = t;
			return TRUE;
		}
		prev = p;
		p = p->next;

		if (p->next == NULL) {
			if (strcmp(p->data, item) == 0) {
				free(p->data);
				free(p);
				prev->next = NULL;
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	} while (1);
	return FALSE;
}
int PowerOfPlenty(set_t* A) {
	if (A == NULL) 
		return -1;
	int n = 0;
	node_t* p = A->head;
	while (p != NULL) {
		++n;
		p = p->next;
	}
	printf("Power of \"%s\": %d\n", A->name, n);
	return 0;
}
int ShowListOfPlenties(void) {
	set_t* p = listOfSets.head;
	printf("{\n");
	if (p == NULL) {
		printf("\n");
	}
	else {
		while (p != NULL) {
			if (p->head != NULL && p->head->data != NULL)
				printf("\"%s\" { \"%s\", ... }\n", p->name, p->head->data);
			else 
				printf("\"%s\" { - }\n", p->name);
			p = p->next;
		}
	}
	printf("}\n");
	return 0;
}
int ShowListOfElements(set_t* A) {
	if (A == NULL)
		return -1;
	printf("\"%s\": ", A->name);
	if(A->head == NULL) {
		printf("{ - }\n");
		return 0;
	}
	node_t* p = A->head;
	printf("{ ");
	while (p != NULL) {
		printf("%c%s%c ", '"', p->data, '"');
		p = p->next;
	}
	printf("}\n");
	return 0;
}

//BINARY OPERATIONS
set_t* DiffPlenties(set_t* A, set_t* B) {
	if (A == NULL || B == NULL)
		return NULL;

	char* nameDiff = malloc(strlen(A->name) + strlen(B->name) + strlen("_diff__and_") + 3);
	if (nameDiff == NULL)
		return NULL;

	itoa(countOfCalls.Diff, nameDiff, 10);
	strcat(nameDiff, "_diff_");
	strcat(nameDiff, A->name);
	strcat(nameDiff, "_and_");
	strcat(nameDiff, B->name);
	set_t* C = CreatePlenty(nameDiff);
	if (C == NULL) {
		free(nameDiff);
		return NULL;
	}
	node_t* pa = A->head, * pb = B->head;

	while (pa != NULL && pb != NULL) {
		if (strcmp(pa->data, pb->data) < 0) {
			AddIntoPlenty(C, pa->data);
			pa = pa->next;
		}
		else if (strcmp(pa->data, pb->data) > 0) {
			pb = pb->next;
		}
		else {
			pa = pa->next;
			pb = pb->next;
		}
	}
	while (pa != NULL) {
		AddIntoPlenty(C, pa->data);
		pa = pa->next;
	}

	countOfCalls.Diff++;
	free(nameDiff);
	return C;
}
set_t* SimmetricDiff(set_t* A, set_t* B) {
	if (A == NULL || B == NULL)
		return NULL;

	char* nameSDiff = malloc(strlen(A->name) + strlen(B->name) + strlen("_sdiff__and_") + 3); 
	if (nameSDiff == NULL)
		return NULL;

	itoa(countOfCalls.SDiff, nameSDiff, 10);
	strcat(nameSDiff, "_sdiff_");
	strcat(nameSDiff, A->name);
	strcat(nameSDiff, "_and_");
	strcat(nameSDiff, B->name);
	set_t* C = CreatePlenty(nameSDiff);
	if (C == NULL) {
		free(nameSDiff);
		return NULL;
	}
	node_t* pa = A->head, * pb = B->head;

	while (pa != NULL && pb != NULL) {
		if (strcmp(pa->data, pb->data) < 0) {
			AddIntoPlenty(C, pa->data);
			pa = pa->next;
		}
		else if (strcmp(pa->data, pb->data) > 0) {
			AddIntoPlenty(C, pb->data);
			pb = pb->next;
		}
		else {
			pa = pa->next;
			pb = pb->next;
		}
	}
	while (pa != NULL) {
		AddIntoPlenty(C, pa->data);
		pa = pa->next;
	}
	while (pb != NULL) {
		AddIntoPlenty(C, pb->data);
		pb = pb->next;
	}

	countOfCalls.SDiff++;
	free(nameSDiff);
	return C;
}
set_t* IntersectionOfPlenties(set_t* A, set_t* B) {
	if (A == NULL || B == NULL)
		return NULL;

	char* nameInter = malloc(strlen(A->name) + strlen(B->name) + strlen("_inter__and_") + 3);
	if (nameInter == NULL)
		return NULL;

	itoa(countOfCalls.Inter, nameInter, 10);
	strcat(nameInter, "_inter_");
	strcat(nameInter, A->name);
	strcat(nameInter, "_and_");
	strcat(nameInter, B->name);
	set_t* C = CreatePlenty(nameInter);
	if (C == NULL) {
		free(nameInter);
		return NULL;
	}
	node_t* pa = A->head, * pb = B->head;

	while (pa != NULL && pb != NULL) {
		if (strcmp(pa->data, pb->data) < 0) {
			pa = pa->next;
		}
		else if (strcmp(pa->data, pb->data) > 0) {
			pb = pb->next;
		}
		else {
			AddIntoPlenty(C, pa->data);
			pa = pa->next;
			pb = pb->next;
		}
	}

	countOfCalls.Inter++;
	free(nameInter);
	return C;
}
int IsOneContainOther(set_t* A, set_t* B) {
	if (A == NULL || B == NULL)
		return -1;

	node_t* pa = A->head, * pb = B->head;

	while (pa != NULL && pb != NULL) {
		if (strcmp(pa->data, pb->data) < 0)
			return FALSE;
		else if (strcmp(pa->data, pb->data) > 0) {
			pb = pb->next;
		}
		else {
			pa = pa->next;
			pb = pb->next;
		}
	}
	if (pa != NULL)
		return FALSE;
	else
		return TRUE;
}
set_t* Union(set_t* A, set_t* B) {
	if (A == NULL || B == NULL)
		return NULL;
	
	char* nameUnion = malloc(strlen(A->name) + strlen(B->name) + strlen("_union__and_") + 3);
	if (nameUnion == NULL)
		return NULL;

	itoa(countOfCalls.Union, nameUnion, 10);
	strcat(nameUnion, "_union_");
	strcat(nameUnion, A->name);
	strcat(nameUnion, "_and_");
	strcat(nameUnion, B->name);
	set_t* C = CreatePlenty(nameUnion);
	if (C == NULL) {
		free(nameUnion);
		return NULL;
	}
	node_t* pa = A->head, * pb = B->head;


	while (pa != NULL && pb != NULL) {
		if (strcmp(pa->data, pb->data) < 0) {
			AddIntoPlenty(C, pa->data);
			pa = pa->next;
		}
		else if (strcmp(pa->data, pb->data) > 0) {
			AddIntoPlenty(C, pb->data);
			pb = pb->next;
		}
		else {
			AddIntoPlenty(C, pa->data);
			pa = pa->next;
			pb = pb->next;
		}
	} 
	while (pa != NULL) {
		AddIntoPlenty(C, pa->data);
		pa = pa->next;
	}
	while (pb != NULL) {
		AddIntoPlenty(C, pb->data);
		pb = pb->next;
	}
	
	countOfCalls.Union++;
	free(nameUnion);
	return C;
}