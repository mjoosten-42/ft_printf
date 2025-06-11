#include "c_string.h"
#include "ft_printf_utils.h"
#include "libft.h"

#include <stdint.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

static const char *get_base(t_data *data) {
	const char *lower = "0123456789abcdef";
	const char *upper = "0123456789ABCDEF";

	if (data->conversion == 'X') {
		return upper;
	} else {
		return lower;
	}
}

static int get_basesize(t_data *data) {
	switch (data->conversion) {
		case 'o':
			return 8;
		case 'd':
		case 'i':
		case 'u':
			return 10;
		case 'x':
		case 'X':
			return 16;
		default:
			return 1;
	}
}

#define CONVERT_INTEGER(signedness, type)                                   \
	convert_integer_##signedness(string output, t_data *data, type value) { \
		string tmp		= string_new(32);                                   \
		int	   basesize = get_basesize(data);                               \
                                                                            \
		if (value < 0) {                                                    \
			string_push_back(tmp, '-');                                     \
		} else if (data->flags.use_sign) {                                  \
			string_push_back(tmp, '+');                                     \
		} else if (data->flags.put_blank) {                                 \
			string_push_back(tmp, ' ');                                     \
		}                                                                   \
                                                                            \
		if (data->flags.use_alternate_form && value != 0) {                 \
			switch (data->conversion) {                                     \
				case 'o':                                                   \
					string_push_back(tmp, '0');                             \
					break;                                                  \
				case 'x':                                                   \
					string_push_back(tmp, '0');                             \
					string_push_back(tmp, 'x');                             \
					break;                                                  \
				case 'X':                                                   \
					string_push_back(tmp, '0');                             \
					string_push_back(tmp, 'X');                             \
					break;                                                  \
				default:                                                    \
					break;                                                  \
			}                                                               \
		}                                                                   \
                                                                            \
		type   value_lower = value / basesize;                              \
		type   i		   = 1;                                             \
		size_t digits	   = 1;                                             \
                                                                            \
		while (value_lower / i) {                                           \
			i *= basesize;                                                  \
			digits++;                                                       \
		}                                                                   \
                                                                            \
		if (data->flags.precision_provided) {                               \
			while (digits++ < data->precision) {                            \
				string_push_back(tmp, '0');                                 \
			}                                                               \
		}                                                                   \
                                                                            \
		while (i > 0) {                                                     \
			int div = value / i;                                            \
                                                                            \
			if (div) {                                                      \
				value -= (div * i);                                         \
			}                                                               \
                                                                            \
			string_push_back(tmp, get_base(data)[ABS(div) % basesize]);     \
                                                                            \
			i /= basesize;                                                  \
		}                                                                   \
                                                                            \
		while (string_length(tmp) < data->width) {                          \
			if (data->flags.left_align) {                                   \
				string_push_back(tmp, ' ');                                 \
			} else if (data->flags.use_zero_padding) {                      \
				string_push_front(tmp, '0');                                \
			} else {                                                        \
				string_push_front(tmp, ' ');                                \
			}                                                               \
		}                                                                   \
                                                                            \
		string_concat(output, tmp);                                         \
		string_delete(tmp);                                                 \
	}

#pragma GCC diagnostic push
// Ignored unsigned < 0 comparison
#pragma GCC diagnostic ignored "-Wtype-limits"
void				   CONVERT_INTEGER(signed, intmax_t);
void				   CONVERT_INTEGER(unsigned, uintmax_t);
#pragma GCC diagnostic pop

void convert_integer(string output, t_data *data, va_list ap) {
	int is_signed = data->conversion == 'd' || data->conversion == 'i';

	if (is_signed) {
		intmax_t value = 0;

		if (!*data->length) {
			value = va_arg(ap, int);
		} else if (!ft_strncmp(data->length, "l", 3)) {
			value = va_arg(ap, long);
		} else if (!ft_strncmp(data->length, "ll", 3)) {
			value = va_arg(ap, long long);
		} else if (!ft_strncmp(data->length, "j", 3)) {
			value = va_arg(ap, intmax_t);
		} else if (!ft_strncmp(data->length, "z", 3)) {
			value = va_arg(ap, ssize_t);
		} else if (!ft_strncmp(data->length, "t", 3)) {
			value = va_arg(ap, ptrdiff_t);
		}

		convert_integer_signed(output, data, value);
	} else {
		uintmax_t value = 0;

		if (!*data->length) {
			value = va_arg(ap, unsigned int);
		} else if (!ft_strncmp(data->length, "l", 2)) {
			value = va_arg(ap, unsigned long);
		} else if (!ft_strncmp(data->length, "ll", 3)) {
			value = va_arg(ap, unsigned long long);
		} else if (!ft_strncmp(data->length, "j", 3)) {
			value = va_arg(ap, uintmax_t);
		} else if (!ft_strncmp(data->length, "z", 3)) {
			value = va_arg(ap, size_t);
		} else if (!ft_strncmp(data->length, "t", 3)) {
			value = va_arg(ap, ptrdiff_t);
		}

		convert_integer_unsigned(output, data, value);
	}
}
