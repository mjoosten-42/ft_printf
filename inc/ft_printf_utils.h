#ifndef FT_PRINTF_UTILS_H
#define FT_PRINTF_UTILS_H

#include "c_string.h"

#include <stdarg.h>

typedef struct {
	unsigned int use_alternate_form : 1;
	unsigned int use_zero_padding : 1;
	unsigned int left_align : 1;
	unsigned int put_blank : 1;
	unsigned int use_sign : 1;
	unsigned int group_thousands : 1;

	unsigned int precision_provided : 1;
} t_flags;

typedef struct {
	t_flags flags;
	size_t	width;
	size_t	precision;
	char	length[3];
	char	conversion;
} t_data;

const char *convert(string output, const char *format, va_list ap);
const char *parse(t_data *data, const char *format);
void		convert_integer(string output, t_data *data, va_list ap);
void		convert_float(string output, t_data *data, va_list ap);
void		convert_other(string output, t_data *data, va_list ap);

#endif
