#include "command.h"
#include "cmdPath.h"
#include "types.h"
#include "pgidTracker.h"
#include "mySignal.h"

/*
Purpose: initializes the command

input: The command - the command must also contain an input string that will be used to initialize the command

output: the command is fully initialized

extra detail: command.input is no longer usable.


*/

void initCommand(struct Command* command) {
        command->argc = tokenize(command->input, command->argv, ' ');
	command->id = 0;
}

int run_built_in_command(struct Command* command) {
	if (str_cmp(command->argv[0], "cd")) {
                if (command->argc > 2) {
                        write(1, "command cd: too many argument\n", 20);
                }
                else if (command->argc == 2){
			if (chdir(command->argv[1]) == -1) {
				write(1, "can't find folder : ", 20);
				write(1, command->argv[1], get_str_line_length(command->argv[1]));
				write(1, "\n",2);
			}
		}
		else {
			chdir(getEnv("HOME="));
		}
		return TRUE;
	}
	else if (str_cmp(command->argv[0], "exit")) {
		int pgid;
		int status;
		while (!myPgidIsEmpty(&mypgids)) {
			pgid = mypgids.pgidList[mypgids.top - 1];
			kill(-pgid, SIGKILL);//don't need to wait because init process will do it once addopted
			popPgids(&mypgids);
		}
		_exit(0);
	}
	else if (str_cmp(command->argv[0], "fg")) {

        }
	else if (str_cmp(command->argv[0], "bg")) {

        }
	else if (str_cmp(command->argv[0], "kill")) {

        }
	return FALSE;

}


int run_command(struct Command* command) {
	char fileBUFFER[MAX_STR_SIZE+1];
        char* file=fileBUFFER;
        int pid = getpid();
        char *concat;
        int child_status;


        if (run_built_in_command(command)){
			command->id = -1;
			return 0;

        }
	else {
		pid = fork();
		command->id = pid;
	}

        if (pid == CHILD) {
		//if the command is a destination
                if (str_contains(command->argv[0],'/')) {
			file = command->argv[0];
		}
		//otherwise use PATH
		else {
			file = searchPath(command->argv[0], getPath());
		}

		if (file == NULL) {
			write(1,"no file found for the command: ", 32);
			write(1,command->argv[0],get_str_line_length(command->argv[0]));
			write(1,"\n",1);
			_exit(0);
		}
                else if (execve(file, command->argv, __environ) == -1) {
                	write(1, "failed to execute command ", 26);
                	write(1, file, get_str_line_length(file));
                	write(1, "\n", 1);
                	_exit(0);
        	}
        }
	//error
        else if (pid == -1) {
        	write(1, "creating child process failed", 29);
        	return 0;
        }
        return 0;
}

