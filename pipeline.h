#ifndef PIPELINE_H
#define PIPELINE_H

#include "command.h"

struct Pipeline {
        char* input;
        int numCommands;
        struct Command* commandList;
};


void pipelineToCommandList(struct Pipeline *pipe);

void initPipeline(char* str, struct Pipeline *pipe);

int runPipeline(struct Pipeline *pipe, char* oPathOption, char* iPathOption);

#endif


