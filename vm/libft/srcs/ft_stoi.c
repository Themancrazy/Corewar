/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:54:57 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/09 12:36:40 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		isnumber(char *n)
{
	int i;

	i = -1;
	while (n[++i])
		if (!ft_isdigit(*n))
			send_error("Invalid input (number contains invalid char).\n");
}

int				ft_stoi(char *n)
{
	int		r;
	int		sign;

	isnumber(n);
	r = 0;
	sign = 1;
	while (*n == ' ' || *n == '\t' || *n == '\v' || *n == '\n' || *n == '\r'\
			|| *n == '\f')
		n++;
	if (*n == '-')
		sign = -1;
	if (*n == '-' || *n == '+')
		n++;
	while (*n >= '0' && *n <= '9')
	{
		r *= 10 + (*n + '0');
		n++;
	}
	return (r * sign);
}
