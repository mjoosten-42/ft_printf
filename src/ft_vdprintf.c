#include "c_string.h"
#include "ft_printf.h"
#include "libft.h"

#include <unistd.h>

#define MAX(a, b) (a > b ? a : b)

size_t special(string output, const char *format, va_list ap);

int ft_vdprintf(int fd, const char *format, va_list ap) {
	string output = string_new(1024);

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

typedef enum e_state {
	PERCENT,
	FLAGS,
	WIDTH,
	PRECISION,
	LENGTH,
	CONVERSION,
	DONE
} t_state;

size_t special(string output, const char *format, va_list ap) {
	t_flags flags				= { 0 };
	t_state state				= PERCENT;
	int		width				= 0;
	int		recording_precision = 0;
	int		precision			= 0;
	char	length_modifier[3]	= { 0 };
	const char *fmt_cpy = format;

	static const char *all_flags			= "#0- +";
	static const char *all_length_modifiers = "hlqLjzZt";
	static const char *all_conversions		= "diouxXeEfFgGaAcsCSPnm%";

	// skip percent
	for (format++; state != DONE; format++) {
		if (state <= FLAGS && ft_strchr(all_flags, *format)) {
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
					flags.put_blank = 1;
					continue;
				case '+':
					flags.use_sign = 1;
					continue;
			}
		}

		state = MAX(state, WIDTH);

		if (state <= WIDTH && ft_isdigit(*format) &&
			(width != 0 || *format != '0')) {
			int digit = *format - '0';

			width = width * 10 + digit;

			continue;
		}

		state = MAX(state, PRECISION);

		if (state <= PRECISION) {
			if (!recording_precision && *format == '.') {
				recording_precision = 1;

				continue;
			}

			if (recording_precision && ft_isdigit(*format)) {
				int digit = *format - '0';

				precision = precision * 10 + digit;

				continue;
			}
		}

		state = MAX(state, LENGTH);

		if (state <= LENGTH && ft_strchr(all_length_modifiers, *format)) {
			length_modifier[0] = *format;

			if (format[0] == 'h' && format[1] == 'h') {
				length_modifier[1] = 'h';
			}

			if (format[0] == 'l' && format[1] == 'l') {
				length_modifier[1] = 'l';
			}

			state = CONVERSION;

			continue;
		}

		state = MAX(state, CONVERSION);

		if (state <= CONVERSION && ft_strchr(all_conversions, *format)) {
			char value;

			switch (*format) {
				case 'd':
				case 'i':
					break;
				case 'c':
					value = va_arg(ap, int);
					break;
				default:
					ft_dprintf(2, "Unhandled conversion: %c\n", *format);
					break;
			};

			(void)value;

			state = DONE;
		}

		// missing conversion
		if (state != DONE) {
			int len = format - fmt_cpy;

			for (; fmt_cpy != format; fmt_cpy++) {
				string_push_back(output, *fmt_cpy);
			}

			return len;			
		}

		break;
	}

	string_push_back(output, *format);
	return 1;
	(void)ap;
	(void)flags;
	(void)state;
	(void)length_modifier;
}
