# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:57:22 by anjansse          #+#    #+#              #
#    Updated: 2019/10/13 17:13:52 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	corewar

GENERAL		=	main.c parser.c run.c champion.c process.c op.c print.c\
				instruction.c gui.c

INSTR		=	ft_live.c ft_ld.c ft_st.c ft_add.c ft_sub.c ft_and.c\
				ft_or.c ft_xor.c ft_zjump.c ft_ldi.c ft_sti.c ft_fork.c\
				ft_lld.c ft_lldi.c ft_lfork.c ft_aff.c

SRCS		=	$(addprefix src/, $(GENERAL) $(addprefix instructions/, $(INSTR)))

INCLUDES	=	-I inc/ -I libft/includes/

CC			=	gcc

NCURSES		=	-lcurses

NUKLEAR		=	-I nuklear/

SDL			=	-I SDL2/include/ -L SDL2/lib -l SDL2-2.0.0

DEBUG		=	-g -fsanitize=undefined -fsanitize=address

CFLAGS		=	-Wall -Wextra -Werror $(NCURSES) $(DEBUG)

LLIB		=	libft.a

reprog: fclean all

all: $(NAME)

$(NAME):
	@echo -n 'Compiling VM...'
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) $(LLIB) -o $(NAME)
	@echo "\t\x1b[92m✓✓\x1b[0m\n"

lib:
	@echo -n 'Compiling libft...'
	@make -C libft/ re
	@cp libft/libft.a .
	@echo "\t\t\x1b[92m✓\x1b[0m\n"

totall: lib all

git:
	@git add .
	@git commit -m "$(C)"
	@git push

clean:
	@rm -rf build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LLIB)
	@rm -rf *.dSYM
	@echo "\t\n\x1b[96mVM \x1b[91mlibrary has been cleaned!\x1b[0m\n"

totfclean: fclean
	@make -C libft/ fclean
	@echo "\x1b[96mLibft has been cleaned.\x1b[0m\t\x1b[91mDon't forget to\
		recompile it...\n\x1b[0m"

re: totfclean totall

tot: totfclean totall
