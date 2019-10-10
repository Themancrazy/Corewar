/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:26:46 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/09 19:09:38 by anjansse         ###   ########.fr       */
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
	char			**av;
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

typedef struct		s_process
{
	void			*pc;
	t_champ			*id;
	struct s_process *next;
}					t_process;

typedef struct      s_cw
{
	t_parser        parsing;
	t_champ			champions[MAX_PLAYERS];
	t_champ			tmp_champ[MAX_PLAYERS];
	int				n_players;
	t_process		*process_list;
	uint8_t			memory[MEM_SIZE];
	t_cycle			cycle;
}                   t_cw;

void				champ_load(t_cw *cw, char *filename, int champ_num);

void				process_init(t_cw *cw, void *pc);

void				corewar_parser(t_cw *cw);
void				corewar_run(t_cw *cw);

#endif
