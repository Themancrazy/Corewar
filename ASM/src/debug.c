/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 09:20:18 by anjansse          #+#    #+#             */
/*   Updated: 2019/11/14 09:20:20 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

void			debug_print_instructions(t_vector *v)
{
	int				i;
	t_instruction	*item;

	i = 0;
	while (i < v->size)
	{
		item = (t_instruction *)vector_get(v, i);
		i++;
	}
}

void			debug_print_labels(t_vector *v)
{
	int			i;
	t_label		*item;

	i = 0;
	while (i < v->size)
	{
		item = (t_label *)vector_get(v, i);
		i++;
	}
}

void			debug_print_darray(char **a)
{
	while (a && *a)
	{
		ft_printf("-> %s\n", *a);
		a++;
	}
}
