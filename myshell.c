#include "myString.h"
#include "types.h"
#include "myMem.h"
#include "command.h"
#include "job.h"
#include <unistd.h>
#include "cmdPath.h"
#include "pgidTracker.h"



char BUFFER[MAX_STR_SIZE + 1];
struct MyPGIDs mypgids;


int main() {
        signal(SIGTTOU, SIG_IGN);

        struct Command command;
        struct Job job;
	int status;
        int bytes;
	char* cwd;
	char name[MAX_STR_SIZE] = "";
	int pgid;
	int tcid = tcgetpgrp(STDIN_FILENO);

	initMyPgids(&mypgids);
        BUFFER[MAX_STR_SIZE] = 0;
        while (1) {
		cwd = getcwd(BUFFER, MAX_STR_SIZE);
		write(1,cwd, get_str_line_length(cwd));
        	write(1," $myshell$ ", 12);
        	bytes = read(0,BUFFER, MAX_STR_SIZE);
        	BUFFER[bytes] = '\0';
		str_cpy(BUFFER, name);
        	initJob(BUFFER, &job);


        	pgid = runPipeline(&job.pipeline, job.outfile_path, job.infile_path);


		if (myPgidIsFull(&mypgids)) {
			write(1, "too many processes running at once\n", 36);
			continue;
		}
		else if (pgid > 0) {
			insertPgids(&mypgids, pgid, name);
		}
		else if (pgid == 0) {
			continue;
		}


		if (job.background == 0) {
			tcsetpgrp(STDIN_FILENO, pgid);
			while(waitpid(-pgid, &status ,WUNTRACED)>0);
			tcsetpgrp(STDIN_FILENO, tcid);
		}
        }
        return 0;
}
