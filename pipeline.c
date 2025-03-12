#include "pipeline.h"
#include "types.h"
#include <fcntl.h>

void pipelineToCommandList(struct Pipeline *pipe)
{
        int i;
        char *tokens[MAX_TOKEN];
        int bytesOfCommands = sizeof(struct Command);
        pipe->numCommands = tokenize(pipe->input, tokens, '|');
        pipe->commandList = (struct Command *)my_allocate(bytesOfCommands * pipe->numCommands);
        for (i = 0; i < pipe->numCommands; i++)
        {
                pipe->commandList[i].input = tokens[i];
        }
}

void initPipeline(char *str, struct Pipeline *pipeLine)
{

        int i;

        pipeLine->input = str;
        pipelineToCommandList(pipeLine);
        for (i = 0; i < pipeLine->numCommands; i++)
        {
                initCommand(&(pipeLine->commandList[i]));
        }
}

int runPipeline(struct Pipeline *pipeLine, char* oPathOption, char* iPathOption)
{
        int i;
        int oldpipefd[2];
        int newpipefd[2];
        int stdstream[2];
        int childStatus;
	int oPathfd;
	int iPathfd;


        stdstream[READ_END] = dup(0);
        stdstream[WRITE_END] = dup(1);

	oPathfd = oPathOption ? open(oPathOption, O_CREAT | O_WRONLY, S_IRWXU) : stdstream[WRITE_END];
	iPathfd = iPathOption ? open(iPathOption, O_RDONLY) : stdstream[READ_END];
	// just need to populate newpipefd with something
	// not important what, but make sure it's not 0 or 1
        newpipefd[0] = dup(0);
	newpipefd[1] = dup(1);


        close(newpipefd[WRITE_END]);

	for (i = 0; i < pipeLine->numCommands; i++)
        {
		//inherit pipe, then create a new one for the next process
                oldpipefd[0] = newpipefd[0];
                oldpipefd[1] = newpipefd[1];
		pipe(newpipefd);
		// clear these pipes, since they're about to be used
                close(1);
                close(0);

		// if first command
                if (i == 0)
                {
                        dup2(iPathfd, 0);
                }
		// if not last command
                if (i < pipeLine->numCommands - 1)
                {
                        dup2(newpipefd[WRITE_END], 1);
                }
		// if not first command
                if (i > 0)
                {
			dup2(oldpipefd[READ_END], 0);
                }
		//if last command
                if (i == pipeLine->numCommands - 1)
                {
                        dup2(oPathfd, 1);
                }

		// if there is error don't run command on commands that use it
		// important to close the file at the bottom then (that is, don't use 'continue')
		if (iPathfd == -1 && i == 0) {
			write(stdstream[WRITE_END], "Input file redirection failed to open\n", 39);
		}
		else if (oPathfd == -1 && i == pipeLine->numCommands - 1) {
			write(stdstream[WRITE_END], "Output file redirection failed to open\n", 40);
		}
		else {
                	run_command(&(pipeLine->commandList[i]));
			setpgid(pipeLine->commandList[i].id, pipeLine->commandList[0].id);
		}
		//close the pipes that were just used
                close(oldpipefd[READ_END]);
		close(newpipefd[WRITE_END]);

        }
	close(newpipefd[READ_END]);
	// we need to restore the original fd into 0 and 1;
	close(1);
	close(0);
	dup2(stdstream[READ_END], 0);
	dup2(stdstream[WRITE_END], 1);
	// close the extra stdout and stdin;
	close(stdstream[READ_END]);
	close(stdstream[WRITE_END]);

	return pipeLine->commandList[0].id;
}

