
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:26:46 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/01 23:27:12 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int             main(int ac, char **av)
{
	if (ac == 1)
		send_error("usage\n");
	corewar(--ac, ++av);
	return (0);
}