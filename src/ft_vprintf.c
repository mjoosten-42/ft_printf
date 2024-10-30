#include "ft_printf.h"

int ft_vprintf(const char *format, va_list ap) {
	return ft_vfprintf(stdout, format, ap);
}
