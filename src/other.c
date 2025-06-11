#define _GNU_SOURCE

#include "c_string.h"
#include "ft_printf_utils.h"
#include "libft.h"

#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>

void convert_other(string output, t_data *data, va_list ap) {
	const void *ptr = NULL;
	string		tmp = string_new(32);

	switch (data->conversion) {
		case 'C':
			data->conversion = 'c';
			data->length[0]	 = 'l';
			data->length[1]	 = '\0';
			return convert_other(output, data, ap);
		case 'c':
			if (!ft_strncmp(data->length, "l", 3)) {
				string_push_back(tmp, va_arg(ap, wint_t));
			} else {
				string_push_back(tmp, va_arg(ap, int));
			}
			break;
		case 'S':
			data->conversion = 's';
			data->length[0]	 = 'l';
			data->length[1]	 = '\0';
			return convert_other(output, data, ap);
		case 's':
			ptr = va_arg(ap, char *);

			string_append(tmp, ptr);

			break;
		case 'p':
			data->flags.use_alternate_form = 1;
			break;
		case 'n':
			ptr = va_arg(ap, int *);

			*(int *)ptr = string_length(output);
			break;
		case 'm':
			if (data->flags.use_alternate_form) {
				string_append(tmp, strerrorname_np(errno));
			} else {
				string_append(tmp, strerror(errno));
			}
			break;
	}

	while (string_length(tmp) < data->width) {
		if (data->flags.left_align) {
			string_push_back(tmp, ' ');
		} else {
			string_push_front(tmp, ' ');
		}
	}

	string_concat(output, tmp);
}
