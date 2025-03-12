#ifndef TYPES_H
#define TYPES_H
//#include <sys/types.h>
//#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STR_SIZE 256
#define MAX_TOKEN MAX_STR_SIZE/2
#define CHILD 0
//#define NULL 0

#define TRUE 1
#define FALSE 0

#define READ_END 0
#define WRITE_END 1

extern char BUFFER[];
extern char* const envp[];
extern struct MyPGIDs mypgids;

#endif


