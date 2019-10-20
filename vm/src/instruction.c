#include "vm.h"

static t_instr_hdlr instruction[] = {
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjump,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_lld,
	ft_lldi,
	ft_lfork,
	ft_aff
};

static void		decode_ocp(t_process *cp, uint8_t *cpc, uint8_t *ret, int trunc)
{
	static uint8_t	arg_length[4] = {0, T_REG, T_DIR, T_IND};
	static uint8_t	arg_length2[4] = {0, T_REG, T_IND, T_IND};
	uint8_t acb;
	int		i;

	i = -1;
	acb = *cpc;
	while (++i < 4)
	{
		if (trunc == 1)
			*ret += arg_length[acb & 0b00000011];
		else
			*ret += arg_length2[acb & 0b00000011];
		acb >>= 2;		
	}
}

/*
** ----------------------------------------------------------------------------
** Function used to chaneg the pc of this process and assign it to the next
** op in memory. It will use the OCP if there's one for this instruction to
** 'jump' the correct size (depanding of the size of parameters - reg, dir, ind).
**
** {t_process *} cp - Pointer to current process.
** ----------------------------------------------------------------------------
*/

static void		pc_next(t_process *cp)
{
	uint8_t		jump_size;

	jump_size = 0;
	if (OCP)
	{
		decode_ocp(cp, ++(cp->pc), &jump_size, g_op_tab[cp->op].trunc);
		cp->pc = (cp->pc + 1 + jump_size);
	}
	else
	{
		if (TRUNC)
			jump_size = T_IND;
		else
			jump_size = g_op_tab[cp->op].param[0];
		cp->pc = (cp->pc + 1 + jump_size);
	}
	cp->op = *(cp->pc) - 1;
}

/*
** ----------------------------------------------------------------------------
** Function used to execute the instruction stored at the pc of this current
** process, then jump the pc to the next op in memory.
**
** {t_cw *} cw - Main structure for corewar.
** {t_process *} cp - Pointer to current process.
** ----------------------------------------------------------------------------
*/

void			instruction_init(t_cw *cw, t_process *cp)
{
	ft_putstr(cp->id->name);
	ft_putstr(":\t");
	instruction[cp->op](cw, cp);
	pc_next(cp);
	cp->init_cycle = CYCLE;
}