/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 23:44:30 by hypark            #+#    #+#             */
/*   Updated: 2019/11/12 23:21:42 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				ft_zjump(t_cw *cw, t_process *cp)
{
	int16_t			offset;

	offset = (int16_t)cp->param_value[0];
	FLAG & FL_VER4 ? printf("P%5d | ", P_I) : 0;
	FLAG & FL_VER4 ? printf("zjmp %d", offset) : 0;
	if (cp->carry == 1 && cp->param_type[0] == T_DIR)
	{
		cp->pc = pc_idx_mod(cp, offset);
		FLAG & FL_VER4 ? printf(" OK\n") : 0;
	}
	else
		FLAG & FL_VER4 ? printf(" FAILED\n") : 0;
}
