/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_references.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 09:20:31 by anjansse          #+#    #+#             */
/*   Updated: 2019/11/14 18:43:16 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

/*
** Gets the value of the reference by checking the offset of the referenced
** label and setting value to the difference. Throws an error if label
** cannot be found. This way of doing is O^n, we consider it ok in the context
** of an assembleur, but an amelioration would be to implemented a direct
** table.
*/

t_error				get_reference(int *value, char *ref, t_vector *labels)
{
	int				i;
	t_label			*label;

	i = -1;
	while (++i < labels->size)
	{
		label = (t_label *)vector_get(labels, i);
		if (ft_strlen(label->name) && !ft_strcmp(ref, label->name))
		{
			*value = label->offset;
			return (NULL);
		}
	}
	return (ft_strjoin("unknown label: ", ref));
}

/*
** Feeds the label references in instructions' arguments with the according
** label offset. Return an error if the label does not exist.
*/

t_error				feed_references(t_vector *instr, t_vector *labels)
{
	int				i;
	int				j;
	t_instruction	*instruction;
	t_error			err;
	int				value;

	err = NULL;
	i = -1;
	while (++i < instr->size)
	{
		instruction = (t_instruction *)vector_get(instr, i);
		j = -1;
		while (++j < instruction->n_args)
		{
			value = 0;
			if (ft_strlen(instruction->args[j].label))
			{
				err = get_reference(&value, instruction->args[j].label, labels);
				if (err)
					return (err);
				instruction->args[j].value = value - instruction->offset;
			}
		}
	}
	return (NULL);
}
