#include "ft_printf.h"

int ft_dprintf(int fd, const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	int ret = vdprintf(fd, format, ap);
	va_end(ap);

	return ret;
}

