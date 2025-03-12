#ifndef MYSTRING_H
#define MYSTRING_H


#include "types.h"

int get_str_line_length(const char* char_ptr);

int str_cmp(const char* lhs, const char* rhs);

int str_cmp_up_to_length(const char* lhs, const char* rhs, int length);

int tokenize(char* string, char** tokens, char delimiter);

void str_cpy(const char* src, char* dest);


char* str_concat(const char* src, char* dest);

char* str_contains(char* str, char target);


#endif // !1



