#include "c_string.h"

#include "libft.h"

#include <stdlib.h>
#include <string.h>

string string_new(size_t initial_size) {
	string str = malloc(sizeof(*str));

	str->begin	  = malloc(initial_size);
	str->end	  = str->begin + 1;
	str->capacity = initial_size;
	*str->begin	  = '\0';

	return str;
}

void string_delete(string str) {
	free(str->begin);
	free(str);
}

size_t string_size(string str) {
	return str->end - str->begin;
}

size_t string_length(string str) {
	return string_size(str) - 1;
}

char *string_data(const string str) {
	return str->begin;
}

void string_reserve(string str, size_t new_cap) {
	if (str->capacity < new_cap) {
		size_t size = string_size(str);
		char *new	= malloc(new_cap);

		memcpy(new, str->begin, string_size(str));

		str->begin	  = new;
		str->end	  = new + size;
		str->capacity = new_cap;
	}
}

void string_push_back(string str, char c) {
	if (string_size(str) == str->capacity) {
		string_reserve(str, str->capacity * 2);
	}

	*(str->end - 1) = c;
	*str->end		= '\0';
	str->end++;
}

void string_push_front(string str, char c) {
	if (string_size(str) == str->capacity) {
		string_reserve(str, str->capacity * 2);
	}

	for (size_t i = string_size(str) + 1; i; i--) {
		str->begin[i] = str->begin[i - 1];
	}

	*str->begin = c;
	str->end++;
}

void string_append(string str, const char *s) {
	string_append_n(str, s, ft_strlen(s));
}

void string_append_n(string str, const char *s, size_t n) {
	string_reserve(str, string_size(str) + n);

	for (size_t i = 0; i < n && s[i]; i++) {
		string_push_back(str, s[i]);
	}
}

void string_concat(string first, string second) {
	string_append(first, second->begin);
}
