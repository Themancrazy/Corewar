/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:26:46 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/09 11:35:16 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdint.h>
# include "libft.h"
# include "op.h"

# define FLAG		cw->parsing.flag

# define CYCLE		cw->cycle.cycle
# define DUMP_CYCLE	cw->cycle.dump_cycle

/*
** ----------------------------------------------------------------------------
** Macros used for paser (flags).
**
** @macro {FL_DUMP} - Macro for defining dump flag.
** ----------------------------------------------------------------------------
*/

# define FL_DUMP (1 << 0) 
# define FL_GUI (1 << 1)

typedef struct      s_parser
{
	int             flag;
	int				ac;
}                   t_parser;

typedef struct		s_cycle
{
	int				cycle;
	int				dump_cycle;
}					t_cycle;

typedef struct		s_champ
{
	char			manual_assign;
	int				prog_number;
	char			*name;
	char			*comment;
	unsigned int	prog_size;
}					t_champ;

typedef struct      s_cw
{
	t_parser        parsing;
	t_champ			champions[MAX_PLAYERS];
	t_champ			tmp_champ[MAX_PLAYERS];
	uint8_t			memory[MEM_SIZE];
	t_cycle			cycle;
}                   t_cw;

void				champ_load(t_cw *cw, char *filename, int champ_num);

void				corewar_parser(t_cw *cw, int ac, char **av);
void				corewar_run(t_cw *cw);

#endif
