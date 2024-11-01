#include "ft_printf.h"
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv) {
	printf("[%s]\n", "test");
	ft_printf("[%s]\n", "test");
}

