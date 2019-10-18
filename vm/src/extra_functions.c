#include "vm.h"

void    h_rev_bytes(void *ptr, size_t n)
{
	size_t	i;
	size_t  half;
	uint8_t *tmp;
	uint8_t swap;

	i = 0;
	half = n / 2;
	tmp = (uint8_t *)ptr;
	while (i < half)
	{
		swap = tmp[i];
		tmp[i] = tmp[n - i - 1];
		tmp[n - i - 1] = swap;
		++i;
	}
}

void	dump_memory(t_cw *cw)
{
	if (GUI)
		endwin();
	print_memory(cw);
	exit(1);
}