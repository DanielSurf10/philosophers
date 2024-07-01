# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/06/20 19:26:26 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CFLAGS		:= -Wextra -Wall -Werror -pthread

HEADERS		:= -I include

SRCS		:= die_logic.c \
				print_mutex_utils.c \
				print_mutex.c \
				philosopher_actions.c \
				main.c \
				arg_validation.c \
				utils.c \
				philosopher.c
OBJS		:= ${SRCS:%.c=obj/%.o}

all: ${NAME}

${NAME}: ${OBJS}
	@cc ${CFLAGS} ${HEADERS} ${OBJS} -o ${NAME}

obj/%.o: %.c philosophers.h
	@mkdir -p ${dir $@}
	@cc ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

clean:
	@rm -rf obj

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
