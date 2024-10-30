#include "ft_printf.h"
#include "c_string.h"

#include <unistd.h>

size_t special(string output, const char *format, va_list ap);

int ft_vdprintf(int fd, const char *format, va_list ap) {
	string output = string_new();

	while (*format) {
		if (*format == '%') {
			format += special(output, format, ap);
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

typedef struct s_flags {
	unsigned int use_alternate_form : 1;
	unsigned int use_zero_padding : 1;
	unsigned int left_align : 1;
	unsigned int put_blank : 1;
	unsigned int use_sign : 1;
} t_flags;

typedef enum e_state { FLAGS, WIDTH, PRECISION, LENGTH, CONVERSION, DONE } t_state;

// %[flags][width][.precision][length modifier]conversion
size_t special(string output, const char *format, va_list ap) {
	t_flags flags = { 0 };
	t_state state = FLAGS;

	for (; state != DONE; format++) {
		if (state <= FLAGS) {
			switch (*format) {
				case '#':
					flags.use_alternate_form = 1;
					continue;
				case '0':
					flags.use_zero_padding = 1;
					continue;
				case '-':
					flags.left_align = 1;
					continue;
				case ' ':
					flags.put_black = 1;
					continue;
				case '+'
					flags.use_sign = 1;
					continue;
				default:
					break;
			}
		}

		if (state <= WIDTH)
	}

	string_push_back(output, *format);
	return 1;
	(void)ap;
	(void)flags;
	(void)state;
}


