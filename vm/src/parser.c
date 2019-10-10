#include "vm.h"

static void			apply_dump(t_cw *cw, char **arg, int dump_arg)
{
	if (dump_arg <= cw->parsing.ac)
	{
		FLAG |= FL_DUMP;
		DUMP_CYCLE = ft_atoi(arg[dump_arg]);
	}
	else
		send_error("Missing dump cycle number.\n");
}

static void			apply_number(t_cw *cw, char **arg, int num, int champ_arg)
{
	int		prog_num;

	if (num <= cw->parsing.ac)
	{
		prog_num = ft_atoi(arg[num]);
		if ((prog_num - 1) >= MAX_PLAYERS || (prog_num - 1) < 0)
			send_error("Assigning program number must be between 1 and MAX_PLAYERS.\n");
		if (cw->champions[prog_num - 1].manual_assign == 1)
			send_error("Player has already been assigned to this number.\n");
		cw->champions[prog_num - 1].manual_assign = 1;
		champ_load(cw, arg[champ_arg], prog_num - 1);
	}
}

static void        parse_flag(t_cw *cw, char **arg, int *curr_arg)
{
	if (ft_strlen(arg[*curr_arg]) != 2)
		send_error("Incorrect flag.\n");
	arg[*curr_arg]++;
	if (*arg[*curr_arg] == 'd')
		apply_dump(cw, arg, ++(*curr_arg));
	else if (*arg[*curr_arg] == 'g')
		FLAG |= FL_GUI;
	else if (*arg[*curr_arg] == 'n')
		apply_number(cw, arg, ++(*curr_arg), ++(*curr_arg));
}

static void		champ_assign(t_cw *cw)
{
	int 		i;
	int			tmp_i;
	void		*pc;

	i = -1;
	tmp_i = 0;
	while (++i < cw->n_players)
	{
		if (cw->champions[i].manual_assign == 0)
		{
			cw->champions[i] = cw->tmp_champ[tmp_i];
			pc = &cw->memory[(MEM_SIZE / cw->n_players) * i];
			process_init(cw, pc);
			++tmp_i;
		}
	}
}

void			corewar_parser(t_cw *cw)
{
	int32_t		i;
	static int	champ_num = 0;

	i = -1;
	while (++i < cw->parsing.ac)
	{
		if (cw->parsing.av[i][0] == '-')
			parse_flag(cw, cw->parsing.av, &i);
		else
		{
			champ_load(cw, cw->parsing.av[i], champ_num);
			champ_num++;
		}
	}
	champ_assign(cw);
}