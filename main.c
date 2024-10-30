#include "ft_printf.h"
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv) {
	ssize_t ret = ft_printf("hello\n");

	printf("ret: %li\n", ret);
}

