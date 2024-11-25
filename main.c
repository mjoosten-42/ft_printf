#include "inc/ft_printf.h"

#include <stdio.h>
#include <sys/types.h>
#include <limits.h>

#define SIZEOF(array) (sizeof(array) / sizeof(*array))

#define LOOP(array, format)                        \
	{                                                            \
		printf("%s\n", #format);                                 \
                                                                 \
		for (unsigned int i = 0; i < SIZEOF(array); i++) {       \
			ft_printf(#format "\n", array[i]); \
			printf(#format "\n", array[i]);    \
		}                                                        \
	}

int main() {
	int ints[] = { -42, 0,			42,			 1,			 -1,		 100,
				   111, 2000000000, -2000000000, INT_MIN, INT_MAX };
	unsigned int uints[] = { 0,			 1,			 42,		 100,		111,
							 2000000000, 2147483647, 4000000000, UINT_MAX };

	long longs[] = { -42,
					 0,
					 42,
					 1,
					 -1,
					 100,
					 111,
					 2000000000,
					 -2000000000,
					 2147483647,
					 -2147483648,
					 LONG_MIN,
					 LONG_MAX,
					 -9000000000000000000L,
					 9000000000000000000L,
					 };

}
