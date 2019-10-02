/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:26:46 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/02 00:18:26 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdint.h>

/*
** ----------------------------------------------------------------------------
** Macros used for paser (flags).
**
** @macro {FL_DUMP} - Macro for defining dump flag.
** ----------------------------------------------------------------------------
*/

# define FL_DUMP (1 << 0) 
# define FL_PLAYER (1 << 1) 
# define FL_GUI (1 << 2) 
# define EXPECT_NUM (1 << 3) 


typedef struct      s_corewar
{
    int32_t         flag;
}                   t_corewar;

#endif
