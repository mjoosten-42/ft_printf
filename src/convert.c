#include "libft.h"
#include "ft_printf_utils.h"
#include "c_string.h"

static const char *all_flags			= "#0- +";
static const char *all_length_modifiers = "hlqLjzZt";
static const char *all_conversions		= "diouxXeEfFgGaAcsCSPnm%";
static const char *integer_conversions  = "diouxX";
static const char *float_conversions    = "aAeEfFgG";

void	convert_int(string output, t_data *data, int value) {
	int i = 100;
	int started = 0;



	string tmp = string_new(32);

	while (i > 0) {
		int div = value / i;

		if (div) {
			value -= (div * i);
			started = 1;
		}

		if (started) {
			string_push_back(tmp, '0' + div);
		}

		i /= 10;	
	}

	printf("str: %s\n", string_data(tmp));
	(void)output;
	(void)data;
}

const char *convert(string output, const char *format, va_list ap) {
	const char *fmt_cpy = format;
	t_data data = { 0 };

	format = parse(&data, format);

	if (!data.conversion) {
		string_append(output, fmt_cpy, format - fmt_cpy);
	
		return format;
	}

	switch (data.conv_type) {
		case INTEGER:
			switch (data.length) {
				case LENGTH_NONE:
					convert_int(output, &data, va_arg(ap, int));
					break;
				case LENGTH_LONG:
					//convert_long(output, &data, va_arg(ap, long));
					break;
				case LENGTH_LONG_LONG:
					//convert_long_long(output, &data, va_arg(ap, long long));
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
		
	string_append(output, fmt_cpy, format - fmt_cpy);
	
	return format;
	
	(void)ap;
}

const char *parse(t_data *data, const char *format) {
	// skip percent
	format++;

	// flags
	while (ft_strchr(all_flags, *format)) {
		switch (*format) {
			case '#':
				data->flags.use_alternate_form = 1;
				continue;
			case '0':
				data->flags.use_zero_padding = 1;
				continue;
			case '-':
				data->flags.left_align = 1;
				continue;
			case ' ':
				data->flags.put_blank = 1;
				continue;
			case '+':
				data->flags.use_sign = 1;
				continue;
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
	if (ft_strchr(all_length_modifiers, *format)) {
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
	if(ft_strchr(all_conversions, *format)) {
		data->conversion = *format++;

		if (ft_strchr(integer_conversions, data->conversion)) {
			data->conv_type = INTEGER;
		}

		if (ft_strchr(float_conversions, data->conversion)) {
			data->conv_type = FLOAT;
		}
	}

	return format;
}

