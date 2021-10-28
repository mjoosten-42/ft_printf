#include "libft/libft.h"

int	ft_printf(const char *format, ...)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			// Something &format
		}
		else
			ft_putchar_fd(format[i], 1);
		i++;
	}
	return (i);
}
