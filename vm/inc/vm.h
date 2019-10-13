/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:26:46 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/13 13:03:51 by anjansse         ###   ########.fr       */
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
	int				kill_cycle;
	int				kc_check;
}					t_cycle;

typedef struct		s_champ
{
	int				fd;
	char			manual_assign;
	int				prog_number;
	char			*name;
	char			*comment;
	unsigned int	prog_size;
}					t_champ;

typedef struct		s_process
{
	int				init_cycle;
	int				carry;
	void			*pc;
	void			*registers[REG_NUMBER + 1];
	t_champ			*id;
	struct s_process *next;
}					t_process;

typedef struct		s_hdr
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

typedef struct      s_cw
{
	t_hdr			header;
	t_parser        parsing;
	t_champ			champions[MAX_PLAYERS];
	t_champ			tmp_champ[MAX_PLAYERS];
	int				n_players;
	int				n_process;
	t_process		*process_list;
	uint8_t			memory[MEM_SIZE];
	t_cycle			cycle;
}                   t_cw;

typedef void(*t_instr_hdlr)(t_cw *, t_process **);

void				instruction_init(t_cw *cw, t_process **cp, uint8_t ocp);

void				champ_load(t_cw *cw, char *filename, int champ_num);

void				print_memory(t_cw *cw);

void				process_init(t_cw *cw, t_champ *id, void *pc);
void				process_update(t_cw *cw);

void				corewar_parser(t_cw *cw);
void				corewar_run(t_cw *cw);

void				ft_live(t_cw *cw, t_process **cp);
void				ft_ld(t_cw *cw, t_process **cp);
void				ft_st(t_cw *cw, t_process **cp);
void				ft_add(t_cw *cw, t_process **cp);
void				ft_sub(t_cw *cw, t_process **cp);
void				ft_and(t_cw *cw, t_process **cp);
void				ft_or(t_cw *cw, t_process **cp);
void				ft_xor(t_cw *cw, t_process **cp);
void				ft_zjump(t_cw *cw, t_process **cp);
void				ft_ldi(t_cw *cw, t_process **cp);
void				ft_sti(t_cw *cw, t_process **cp);
void				ft_fork(t_cw *cw, t_process **cp);
void				ft_lld(t_cw *cw, t_process **cp);
void				ft_lldi(t_cw *cw, t_process **cp);
void				ft_lfork(t_cw *cw, t_process **cp);
void				ft_aff(t_cw *cw, t_process **cp);

#endif
