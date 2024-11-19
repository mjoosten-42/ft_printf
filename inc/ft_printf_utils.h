#ifndef FT_PRINTF_UTILS_H
#define FT_PRINTF_UTILS_H

#include <stdarg.h>
#include "c_string.h"

typedef enum {
	LENGTH_NONE,
	LENGTH_CHAR,
	LENGTH_SHORT,
	LENGTH_LONG,
	LENGTH_LONG_LONG,
	LENGTH_LONG_DOUBLE,
	LENGTH_INTMAX_T,
	LENGTH_SIZE_T,
	LENGTH_PTRDIFF_T,
} e_length;

typedef enum {
	OTHER,
	INTEGER,
	FLOAT,
} e_conv_type;

typedef struct {
	unsigned int use_alternate_form : 1;
	unsigned int use_zero_padding : 1;
	unsigned int left_align : 1;
	unsigned int put_blank : 1;
	unsigned int use_sign : 1;
} t_flags;

typedef struct {
	t_flags	 flags;
	int		 width;
	int		 precision;
	e_length length;
	char	 conversion;
	e_conv_type conv_type;
} t_data;

const char *convert(string output, const char *format, va_list ap);
const char *parse(t_data *data, const char *format);

#endif
