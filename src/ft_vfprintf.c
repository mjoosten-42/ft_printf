#include "ft_printf.h"
#include <stdio.h>

int ft_vfprintf(FILE *stream, const char *format, va_list ap) {
	return ft_vdprintf(fileno(stream), format, ap);
}

