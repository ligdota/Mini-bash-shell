#ifndef COMMAND_H
#define COMMAND_H
#include "types.h"
#include <unistd.h>
#include "myString.h"
#include "myMem.h"
#define MAX_ARGS MAX_TOKEN

struct Command {
        char* argv[MAX_ARGS + 1];
        unsigned int argc;
        char* input;
        int id;
};

int run_command(struct Command* command);

void initCommand(struct Command* command);

#endif // !1


