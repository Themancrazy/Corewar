/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:14:58 by hypark            #+#    #+#             */
/*   Updated: 2019/11/13 22:07:37 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw - .
** {t_process *} cp - .
** ----------------------------------------------------------------------------
*/

static inline int32_t		indirect_process(t_cw *cw, t_process *cp, int i)
{
	int16_t			address;
	int32_t			param;
	int8_t			*param_byte;

	param_byte = (int8_t *)(&param);
	address = (int16_t)cp->param_value[i];
	address = pc_idx_mod(cp, address);
	i = -1;
	while (++i < 4)
	{
		*param_byte = cw->memory[(address + i) % MEM_SIZE];
		param_byte++;
	}
	swap_int32(&param);
	return (param);
}

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw - .
** {t_process *} cp - .
** ----------------------------------------------------------------------------
*/

static inline int32_t		param_1(t_cw *cw, t_process *cp)
{
	if (cp->param_type[0] == T_DIR)
		return (cp->param_value[0]);
	else if (cp->param_type[0] == T_IND)
		return (indirect_process(cw, cp, 0));
	else
		return (0);
}

void						ft_ld(t_cw *cw, t_process *cp)
{
	int32_t			copy;

	copy = param_1(cw, cp);
	cp->registers[cp->param_value[1]] = copy;
	cp->carry = modify_carry(copy);
	FLAG & FL_VER4 ? ft_printf("P%5d | ", P_I) : 0;
	FLAG & FL_VER4 ? ft_printf("ld %d r%d\n", copy, cp->param_value[1]) : 0;
}
