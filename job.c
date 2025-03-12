#include "myString.h"
#include "pipeline.h"
#include "job.h"
#include <stdio.h>

char checkBackground(char *str)
{
	char* targetLoc = str_contains(str, '&');
    	if (targetLoc  == NULL) {
		return FALSE;
	}
	else {
		*targetLoc = '\0';
		return TRUE;
	}
}

char *checkOutputRedirection(char *str)
{
    	char *tokens[MAX_TOKEN];
    	char *args[MAX_TOKEN];
    	int numArgs;
	char oRedirectionFlag = str_contains(str, '>') != NULL;
    	int numTokens = tokenize(str, tokens, '>');
	// the tokens[0] is left of the redirection token


	if (numTokens > 2) {
        	write(1, "Error more than one output redirection, no output redirection will be done\n", 76);
        	return NULL;
       	}

        /* there is one output redirection */
    	if (numTokens == 2)
    	{
        	numArgs = tokenize(tokens[1], args, ' ');
		//one filename specified
        	if (numArgs == 1)
        	{
            		return args[0];
        	}
		// no filename specified
		else if (numArgs == 0) {
			write(1, "Error no output filename specified\n",36);
			return NULL;
		}
		// more than one filename specified
		else {
			write(1, "Error multiple output filename specified, only the first one specified will be used\n", 85);
			return args[0];
		}
    	}
	// redirection specified but no filename given
	// note there is two errors with this message:
	// the top one is for if there's white space after the out redir token
	// but the one below is if there isn't white space after the out redir token
	if (oRedirectionFlag == TRUE) {
		write(1, "Error no output filename specified\n",36);
	}

	//no redirection

    	return NULL;
}

char *checkInputRedirection(char *str)
{
        char *tokens[MAX_TOKEN];
        char *args[MAX_TOKEN];
        int numArgs;
        char oRedirectionFlag = str_contains(str, '<') != NULL;
        int numTokens = tokenize(str, tokens, '<');
        // the tokens[0] is left of the redirection token


        if (numTokens > 2) {
                write(1, "Error more than one output redirection, no output redirection will be done\n",76);
                return NULL;
        }

        /* there is one output redirection */
        if (numTokens == 2)
        {
                numArgs = tokenize(tokens[1], args, ' ');
                //one filename specified
                if (numArgs == 1)
                {
                        return args[0];
                }
                // no filename specified
                else if (numArgs == 0) {
                        write(1, "Error no output filename specified\n",36);
                        return NULL;
                }
                // more than one filename specified
                else {
                        write(1, "Error multiple output filename specified, only the first one specified will be used\n",85);
                        return args[0];
                }
        }
        // redirection specified but no filename given
        // note there is two errors with this message:
        // the top one is for if there's white space after the out redir token
        // but the one below is if there isn't white space after the out redir token
        if (oRedirectionFlag == TRUE) {
                write(1, "Error no output filename specified\n",36);
        }


        //no redirection
        return NULL;

}

    void setJobOptions(struct Job *job)
    {
        job->background = checkBackground(job->input);
        job->outfile_path = checkOutputRedirection(job->input);
        job->infile_path = checkInputRedirection(job->input);
    }


    void initJob(char* str, struct Job *job) {
        job->input = my_allocate(get_str_line_length(BUFFER));
        str_cpy(BUFFER, job->input);
        setJobOptions(job);
        initPipeline(job->input, &(job->pipeline));
        return;
    }
