#include "mySignal.h"



void foreground_set_and_wait(int pgid) {
        tcsetpgrp(STDIN_FILENO, pgid);
        while(waitpid(-pgid, &status, WUNTRACED) > 0);
        tcsetpgrp(STDIN_FILENO, getpgrp());
}

