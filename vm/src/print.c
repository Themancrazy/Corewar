/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 00:22:28 by hypark            #+#    #+#             */
/*   Updated: 2019/11/13 09:47:56 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ----------------------------------------------------------------------------
** Print in one block of hexadecimal.
**
** {unsigned char} c - Number to print in base 16.
** ----------------------------------------------------------------------------
*/

void			h_puthex(unsigned char c)
{
	static char	*base = "0123456789abcdef";

	printf("%c", base[c / 16]);
	printf("%c", base[c % 16]);
}

/*
** ----------------------------------------------------------------------------
** Print current state of memory to stdout.
**
** {t_cw *} cw - Main structure of the vm.
** ----------------------------------------------------------------------------
*/

void			print_memory(t_cw *cw)
{
	int			i;
	unsigned	siz;

	i = 0;
	siz = (unsigned)sqrt(MEM_SIZE);
	while (i < MEM_SIZE)
	{
		if (i % siz == 0)
		{
			if (i)
				printf("\n");
			if (i == 0)
				printf("0x0000 : ");
			else
				printf("%#06x : ", i);
		}
		h_puthex(cw->memory[i]);
		printf(" ");
		i++;
	}
	printf("\n");
}
