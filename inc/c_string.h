#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef struct s_string {
	char	 *begin;
	char	 *end;
	size_t capacity;
} t_string;

typedef t_string *string;

string string_new();
void   string_delete(string str);

size_t string_size(const string str);
size_t string_length(const string str);
char	 *string_data(const string str);

void string_reserve(string str, size_t size);
void string_push_back(string str, char c);

#endif