#include "inc/ft_printf.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZEOF(array) (sizeof(array) / sizeof(*array))

#define COMPARE(format, ...)\
{\
	ft_printf(format "\n" __VA_OPT__(,) __VA_ARGS__);	\
	printf(format "\n" __VA_OPT__(,)  __VA_ARGS__);	\
}

#define LOOP(array, format)                                \
	{                                                      \
		printf("[%s]\n", format);                          \
                                                           \
		for (unsigned int i = 0; i < SIZEOF(array); i++) { \
			COMPARE(format, array[i]);                 \
		}                                                  \
	}

int main() {
	int nothing[0];
	int				   ints[]	 = { 0, 1, 42, 111, INT_MAX, -1, -42, INT_MIN };
	unsigned int	   uints[]	 = { 0, 1, 42, 111, INT_MAX, UINT_MAX };
	long			   longs[]	 = { 0, 1, 42, 111, INT_MAX, -1, -42, INT_MIN, LONG_MAX, LONG_MIN };
	unsigned long	   ulongs[]	 = { 0, 1, 42, 111, INT_MAX, LONG_MAX, ULONG_MAX };
	long long		   llongs[]	 = { 0, 1, 42, 111, INT_MAX, -1, -42, INT_MIN, LONG_MAX, LONG_MIN ,LLONG_MIN, LLONG_MAX };
	unsigned long long ullongs[] = { 0, 1, 42, 111, INT_MAX, LONG_MAX, ULONG_MAX, ULLONG_MAX };
	const char		   *strs[]	 = { "", "ft_printf" };

	LOOP(ints, "%20i");
	LOOP(uints, "%20u");
	LOOP(longs, "%20li");
	LOOP(ulongs, "%20lu");
	LOOP(llongs, "%20lli");
	LOOP(ullongs, "%20llu");

	LOOP(strs, "%20s");
	LOOP(strs, "%20p");

	close(-1);

	COMPARE("%m");
	COMPARE("%#m");
}
