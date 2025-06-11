#include "c_string.h"
#include "ft_printf_utils.h"
#include "libft.h"

static const char *flags			   = "#0- +'";
static const char *length_modifiers	   = "hlqLjzZt";
static const char *conversions		   = "diouxXeEfFgGaAcsCSPnm%";
static const char *integer_conversions = "diouxX";
static const char *float_conversions   = "aAeEfFgG";

const char *convert(string output, const char *format, va_list ap) {
	const char *fmt_cpy = format;
	t_data		data	= { 0 };

	format = parse(&data, format);

	if (!data.conversion) {
		string_append_n(output, fmt_cpy, format - fmt_cpy);

		return format;
	}

	if (data.conversion == '%') {
		string_push_back(output, '%');

		return format;
	}

	if (ft_strchr(integer_conversions, data.conversion)) {
		convert_integer(output, &data, ap);
	}

	// TODO
	else if (ft_strchr(float_conversions, data.conversion)) {
		convert_float(output, &data, ap);
	}

	// TODO
	else {
		convert_other(output, &data, ap);
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
	while (ft_isdigit(*format) && !(*format == '0' && !ft_isdigit(format[-1]))) {
		data->width = data->width * 10 + *format++ - '0';
	}

	// precision
	if (*format == '.') {
		data->flags.precision_provided = 1;

		format++;

		while (ft_isdigit(*format)) {
			data->precision = data->precision * 10 + *format++ - '0';
		}
	}

	// length
	if (ft_strchr(length_modifiers, *format)) {
		data->length[0] = *format++;

		if (*format == 'h' || *format == 'l') {
			data->length[1] = *format++;
		}

		if (data->length[0] == 'q') {
			data->length[0] = 'l';
			data->length[1] = 'l';
		}

		if (data->length[0] == 'Z') {
			data->length[0] = 'z';
		}
	}

	// conversion
	if (ft_strchr(conversions, *format)) {
		data->conversion = *format++;
	}

	return format;
}
