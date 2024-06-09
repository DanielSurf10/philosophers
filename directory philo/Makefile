# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/06/08 22:11:33 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
# CFLAGS		:= -Wextra -Wall -Werror -g3
CFLAGS		:= -g3

HEADERS		:= -I include

SRCS		:= ${shell find src -iname "*.c"}		# Não esquecer de mudar isso aqui
OBJS		:= ${SRCS:src/%.c=obj/%.o}

all: ${NAME}
bonus: all

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${HEADERS} ${OBJS} -o ${NAME}

obj/%.o: src/%.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

clean:
	@rm -rf obj

fclean: clean
	@rm -f ${NAME}

val: readline.supp all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				--tool=helgrind \
				--tool=drd \
				./${NAME}

re: fclean all

.PHONY: all clean fclean re val
