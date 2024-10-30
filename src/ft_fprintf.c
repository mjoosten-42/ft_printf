#include "ft_printf.h"
#include <stdio.h>

int ft_fprintf(FILE *stream, const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	int ret = ft_vfprintf(stream, format, ap);
	va_end(ap);

	return ret;
}

