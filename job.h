#ifndef JOB_H
#define JOB_H

#include "pipeline.h"
struct Job {
     char* input;
     struct Pipeline pipeline;
     unsigned int num_stages;
     char *outfile_path;          /* NULL for no output redirection     */
     char *infile_path;           /* NULL for no input redirection      */
     int background;              /* 0=foreground, otherwise=background */
};

/* returns a bool */
char checkBackground(char* str);

char* checkOutputRedirection(char* str);

char* checkInputRedirection(char* str);

void setJobOptions(struct Job* job);

void initJob(char* str, struct Job* job);


#endif

