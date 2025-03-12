#include <unistd.h>
#include "types.h"
#include "pgidTracker.h"
#include "myString.h"

void initMyPgids(struct MyPGIDs* mypgids) {
	mypgids->top = 0;
}

int myPgidIsFull (const struct MyPGIDs* mypgids) {
	return mypgids->top == MAX_BACKGROUND_PROCESS;
}

int myPgidIsEmpty (const struct MyPGIDs* mypgids) {
	return mypgids->top == 0;
}

void insertPgids(struct MyPGIDs* mypgids, const int pgid, const char* name) {
	mypgids->pgidList[mypgids->top] = pgid;
	str_cpy(name, mypgids->pgidNameList[mypgids->top]);
	mypgids->top++;
}

void popPgids(struct MyPGIDs* mypgids) {
	mypgids->top--;
}

