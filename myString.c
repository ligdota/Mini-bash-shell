#include "myString.h"
#include "types.h"



void checkForNullptr(const char* ptr, char* msg) {
	if (!ptr) {
		write(1,msg, get_str_line_length(msg) + 1);
	}
};

/*
Purpose: get the length of a line/string

input: char array (string)

output: length of the input string as int.
*/
int get_str_line_length(const char* char_ptr) {
        const char STRING_END = '\n';
        int counter = 0;

        while ((*char_ptr) != STRING_END && *char_ptr != '\0') {
                counter++;
                char_ptr++;
        }

        return counter;
}

/*
Purpose: compares two strings to see if they're equawl

input: two char arrays (string)

output: true/false as an int.
*/


int str_cmp(const char* lhs, const char* rhs) {
	checkForNullptr(lhs, "nullptr in str_cmp");
	checkForNullptr(rhs, "nullptr in str_cmp");

        while (*lhs == *rhs && *lhs != '\0' && *lhs != '\n') {
                lhs++;
                rhs++;
        }

        return *lhs == *rhs && (*lhs == '\0' || *lhs == '\n');
}

void str_cpy(const char* src, char* dest) {
	checkForNullptr(src, "nullptr in str_cpy");
	checkForNullptr(dest, "nullptr in str_cpy");
        while (*src) {
                *dest = *src;
                dest++; src++;
        }
        *dest = *src;
        return;
}

char* str_concat(const char* src, char* dest) {
        checkForNullptr(src, "nullptr in str_concat");
	checkForNullptr(dest, "nullptr in str_concat");

	char* ret = dest;
        while (*dest) {
                dest++;
        }
        str_cpy(src, dest);
        return ret;
}


int tokenize(char* string, char** tokens, char delimiter) {
        checkForNullptr(string, "nullptr in tokenize");
	int counter = 0;
        int flag = 0;

        /* if no leading zeros set tokens[0] here */
        if (*string != '\0' && *string != '\n' && *string != delimiter) {
        	*tokens = string;
        	tokens++;
        	counter++;
        }

        /* go through entire line */
        while (*string != '\0' && *string != '\n') {
        	/* go to next whitespace */
        	while (*string != delimiter && *string != '\0' && *string != '\n') {
        		string++;
        	}
        	/* go to next token */
        	while (*string == delimiter) {
        		*string = '\0';
        		string++;
        	}

        	/* if new line then null terminate and return*/
        	if (*string == '\n') {
        		*string = '\0';
        		return counter;
        	}

        	/* set new token */
        	if (*string != '\0' && *string != '\n') {
        		*tokens = string;
        		tokens++;
        		counter++;
        	}
        }
        return counter;
}
        /*return pointer to first occurence of target*/
char* str_contains(char* str, char target) {
        checkForNullptr(str, "nullptr in str_contains");
	while (*str != '\n' && *str != '\0') {
        	if (*str == target) {
        		return str;
        	}
        	str++;
        }
        return NULL;
}

int str_cmp_up_to_length(const char *lhs, const char *rhs, int length ) {
	checkForNullptr(lhs, "nullptr in str cmp up to length");
	checkForNullptr(rhs, "nullptr in str cmp up to length");

	for (int i = 0; i < length; i++) {
		if (*lhs == '\0' || *rhs == '\0' || *lhs != *rhs) {
			return FALSE;
		}
		lhs++;
		rhs++;
	}
	return TRUE;
}
