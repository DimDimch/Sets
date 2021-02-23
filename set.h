#pragma once

#define PLENTY_MAX_COMMAND_LEN 30
#define PLENTY_MAX_ITEM_LEN 80
#define PLENTY_MAX_REPORT_LEN (PLENTY_MAX_ITEM_LEN + PLENTY_MAX_COMMAND_LEN)
#define RANGE_OF_VALUES(x) ((x >= 32 && x <= 127) && (x != '"'))

typedef char* data_t;

typedef struct node_t {
	data_t data;
	struct node_t* next;
} node_t;

typedef struct set_t{
	char* name;
	node_t* head;
	struct set_t* next;
} set_t;

typedef struct {
	set_t* head;
}setList_t;
