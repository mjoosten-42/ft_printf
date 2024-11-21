#include "inc/ft_printf.h"

#include <stdio.h>
#include <sys/types.h>
#include <limits.h>

#define SIZEOF(array) (sizeof(array) / sizeof(*array))

#define LOOP(array, flags, width, format)                        \
	{                                                            \
		printf("%s\n", #format);                                 \
                                                                 \
		for (unsigned int i = 0; i < SIZEOF(array); i++) {       \
			ft_printf("%" #flags #width #format "\n", array[i]); \
			printf("%" #flags #width #format "\n", array[i]);    \
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

	ft_printf("%+i\n", 42);

	LOOP(ints, , 20, i);
	LOOP(uints, , 20, o);
	LOOP(uints, , 20, u);
	LOOP(uints, , 20, x);
	LOOP(uints, , 20, X);
	LOOP(uints, #, 20, o);
	LOOP(uints, #, 20, x);
	LOOP(uints, #, 20, X);
	LOOP(ints, +, 20, i);
	LOOP(longs, , 20, li);
}
