#include "myString.h"
#include <unistd.h>
#include "types.h"
#include "myMem.h"
#include <sys/stat.h>
#include <stdio.h>

char* getEnv(const char* key) {
	int i;
	int len = get_str_line_length(key);
	for (i = 0;__environ[i] != NULL; i++) {
		if (str_cmp_up_to_length(__environ[i], key, len)) {
			return __environ[i] + len;	
		}
	}
	//default path
	return "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
}

char* getPath() {
	return getEnv("PATH=");
}


char* searchPath(char* command, char* path) {

	char modified_path[MAX_STR_SIZE];
	char* tokens[MAX_TOKEN];
	int directories;
	int i;
	int bytes;
	char* ret;
	str_cpy(path, modified_path);
	directories = tokenize(modified_path, tokens, ':');
	for (i = 0; i < directories; i++) {
		struct stat sb;
		str_cpy(tokens[i], modified_path);
		str_concat("/", modified_path);
		str_concat(command, modified_path);
		if (stat(modified_path, &sb) == 0 && 
			S_ISREG(sb.st_mode) &&
         		(sb.st_mode & S_IXUSR)) {
			bytes = get_str_line_length(modified_path);
        		ret = my_allocate(bytes);
        		str_cpy(modified_path, ret);
        		return ret;
        	}
	}
	return NULL;
}
