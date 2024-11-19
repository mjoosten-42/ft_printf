#include "c_string.h"
#include "ft_printf.h"
#include "ft_printf_utils.h"
#include "libft.h"

#include <unistd.h>

int ft_vdprintf(int fd, const char *format, va_list ap) {
	string output = string_new(1024);

	while (*format) {
		if (*format == '%') {
			format = convert(output, format, ap);
		} else {
			string_push_back(output, *format);
			format++;
		}
	}

	int length = string_length(output);
	int ret	   = write(fd, string_data(output), length);

	string_delete(output);

	return ret;
}
