#include "c_string.h"
#include "ft_printf_utils.h"
#include "libft.h"

// TODO: ' flag
static const char *flags			   = "#0- +'";
static const char *length_modifiers	   = "hlqLjzZt";
static const char *conversions		   = "diouxXeEfFgGaAcsCSPnm%";
static const char *integer_conversions = "diouxX";
static const char *float_conversions   = "aAeEfFgG";

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define CONVERT_INTEGER_PREPARE_UNSIGNED(data, string, value) \
	if (data.flags.use_sign) {                                \
		string_push_back(string, '+');                        \
	} else if (data.flags.put_blank) {                        \
		string_push_back(string, ' ');                        \
	}

// put in macros to prevent errors about useless comparisons
#define CONVERT_INTEGER_PREPARE_SIGNED(data, string, value)    \
	if (value < 0) {                                           \
		string_push_back(string, '-');                         \
	} else {                                                   \
		CONVERT_INTEGER_PREPARE_UNSIGNED(data, string, value); \
	}

#define CONVERT_INTEGER_PREPARE(data, string, value, signedness) \
	CONVERT_INTEGER_PREPARE_##signedness(data, string, value);

#define CONVERT_INTEGER(type, base, signedness, prefix)        \
	{                                                          \
		type   value	= va_arg(ap, type);                    \
		int	   basesize = ft_strlen(base);                     \
		string tmp		= string_new(32);                      \
                                                               \
		/* sign */                                             \
		CONVERT_INTEGER_PREPARE(data, tmp, value, signedness); \
		string_append(tmp, prefix, ft_strlen(prefix));         \
                                                               \
		/* alternate form */                                   \
		if (data.flags.use_alternate_form && value != 0) {     \
			switch (data.conversion) {                         \
				case 'o':                                      \
					string_push_back(tmp, '0');                \
					break;                                     \
				case 'x':                                      \
					string_append(tmp, "0x", 2);               \
					break;                                     \
				case 'X':                                      \
					string_append(tmp, "0X", 2);               \
					break;                                     \
				default:                                       \
					break;                                     \
			}                                                  \
		}                                                      \
                                                               \
		type i			 = 1;                                  \
		type value_lower = value / basesize;                   \
                                                               \
		while (value_lower / i) {                              \
			i *= basesize;                                     \
		}                                                      \
                                                               \
		while (i > 0) {                                        \
			int div = value / i;                               \
                                                               \
			if (div) {                                         \
				value -= (div * i);                            \
			}                                                  \
                                                               \
			string_push_back(tmp, base[ABS(div)]);             \
                                                               \
			i /= basesize;                                     \
		}                                                      \
                                                               \
		/* alignment and padding */                            \
		while (string_length(tmp) < data.width) {              \
			if (data.flags.left_align) {                       \
				string_push_back(tmp, ' ');                    \
			} else if (data.flags.use_zero_padding) {          \
				string_push_front(tmp, '0');                   \
			} else {                                           \
				string_push_front(tmp, ' ');                   \
			}                                                  \
		}                                                      \
                                                               \
		string_concat(output, tmp);                            \
		string_delete(tmp);                                    \
	}

const char *convert(string output, const char *format, va_list ap) {
	const char *fmt_cpy = format;
	t_data		data	= { 0 };

	format = parse(&data, format);

	if (!data.conversion) {
		string_append(output, fmt_cpy, format - fmt_cpy);

		return format;
	}

	if (data.conversion == '%') {
		string_push_back(output, '%');

		return format;
	}

	// TODO: shorten
	if (ft_strchr(integer_conversions, data.conversion)) {
		switch (data.length) {
			case LENGTH_NONE:
				switch (data.conversion) {
					case 'd':
					case 'i':
						CONVERT_INTEGER(int, "0123456789", SIGNED, "");
						break;
					case 'o':
						CONVERT_INTEGER(unsigned int, "01234567", UNSIGNED, "");
						break;
					case 'u':
						CONVERT_INTEGER(
							unsigned int, "0123456789", UNSIGNED, "");
						break;
					case 'x':
						CONVERT_INTEGER(
							unsigned int, "0123456789abcdef", UNSIGNED, "");
						break;
					case 'X':
						CONVERT_INTEGER(
							unsigned int, "0123456789ABCDEF", UNSIGNED, "");
						break;
					default:
						break;
				}
				break;
			case LENGTH_LONG:
				switch (data.conversion) {
					case 'd':
					case 'i':
						CONVERT_INTEGER(long int, "0123456789", SIGNED, "");
						break;
					case 'o':
						CONVERT_INTEGER(
							long unsigned int, "01234567", UNSIGNED, "");
						break;
					case 'u':
						CONVERT_INTEGER(
							long unsigned int, "0123456789", UNSIGNED, "");
						break;
					case 'x':
						CONVERT_INTEGER(long unsigned int,
										"0123456789abcdef",
										UNSIGNED,
										"");
						break;
					case 'X':
						CONVERT_INTEGER(long unsigned int,
										"0123456789ABCDEF",
										UNSIGNED,
										"");
						break;
					default:
						break;
				}
				break;
			case LENGTH_LONG_LONG:
				switch (data.conversion) {
					case 'd':
					case 'i':
						CONVERT_INTEGER(
							long long int, "0123456789", SIGNED, "");
						break;
					case 'o':
						CONVERT_INTEGER(
							long long unsigned int, "01234567", UNSIGNED, "");
						break;
					case 'u':
						CONVERT_INTEGER(
							long long unsigned int, "0123456789", UNSIGNED, "");
						break;
					case 'x':
						CONVERT_INTEGER(long long unsigned int,
										"0123456789abcdef",
										UNSIGNED,
										"");
						break;
					case 'X':
						CONVERT_INTEGER(long long unsigned int,
										"0123456789ABCDEF",
										UNSIGNED,
										"");
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	// TODO
	else if (ft_strchr(float_conversions, data.conversion)) {

	}

	// TODO
	else {
	}

	return format;
}

const char *parse(t_data *data, const char *format) {
	// skip percent
	format++;

	// flags
	while (ft_strchr(flags, *format)) {
		switch (*format) {
			case '#':
				data->flags.use_alternate_form = 1;
				break;
			case '0':
				data->flags.use_zero_padding = 1;
				break;
			case '-':
				data->flags.left_align = 1;
				break;
			case ' ':
				data->flags.put_blank = 1;
				break;
			case '+':
				data->flags.use_sign = 1;
				break;
			case '\'':
				data->flags.group_thousands = 1;
				break;
		}

		format++;
	}

	// width
	while (ft_isdigit(*format) &&
		   !(*format == '0' && !ft_isdigit(format[-1]))) {
		data->width = data->width * 10 + *format++ - '0';
	}

	// precision
	if (*format == '.') {
		format++;

		while (ft_isdigit(*format)) {
			data->precision = data->precision * 10 + *format++ - '0';
		}
	}

	// length
	if (ft_strchr(length_modifiers, *format)) {
		switch (*format) {
			case 'h':
				data->length = LENGTH_SHORT;

				if (format[1] == 'h') {
					data->length = LENGTH_CHAR;
					format++;
				}

				break;
			case 'l':
				data->length = LENGTH_LONG;

				if (format[1] == 'l') {
					data->length = LENGTH_LONG_LONG;
					format++;
				}

				break;
			case 'q':
				data->length = LENGTH_LONG_LONG;
				break;
			case 'L':
				data->length = LENGTH_LONG_DOUBLE;
				break;
			case 'j':
				data->length = LENGTH_INTMAX_T;
				break;
			case 'z':
			case 'Z':
				data->length = LENGTH_SIZE_T;
				break;
			case 't':
				data->length = LENGTH_PTRDIFF_T;
				break;
			default:
				break;
		}

		format++;
	}

	// conversion
	if (ft_strchr(conversions, *format)) {
		data->conversion = *format++;
	}

	return format;
}
