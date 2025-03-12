#ifndef PGIDTRACKER_H
#define PGIDTRACKER_H

#include "myString.h"
#include <unistd.h>

#define MAX_BACKGROUND_PROCESS 100

struct MyPGIDs {
	int pgidList[MAX_BACKGROUND_PROCESS];
	char pgidNameList[MAX_BACKGROUND_PROCESS][MAX_STR_SIZE];
	int top;
};

void initMyPgids(struct MyPGIDs* mypgids);

int myPgidIsFull(const struct MyPGIDs* mypgids);

int myPgidIsEmpty(const struct MyPGIDs* mypgids);


void insertPgids(struct MyPGIDs* mypgids, const int pgid, const char* name);

void popPgids(struct MyPGIDs* mypgids);













#endif
