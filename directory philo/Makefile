# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/06/13 23:31:21 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
# CFLAGS		:= -Wextra -Wall -Werror -g3 -pthread
CFLAGS		:= -g3 -pthread

HEADERS		:= -I include

SRCS		:= ${shell find src -iname "*.c"}		# Não esquecer de mudar isso aqui
OBJS		:= ${SRCS:src/%.c=obj/%.o}

all: ${NAME}
bonus: all

${NAME}: ${OBJS}
	@cc ${CFLAGS} ${HEADERS} ${OBJS} -o ${NAME}

obj/%.o: src/%.c include/philosophers.h
	@mkdir -p ${dir $@}
	@cc ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

clean:
	@rm -rf obj

fclean: clean
	@rm -f ${NAME}

val: all
	@valgrind -q --leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

hell: all
	@valgrind -q --tool=helgrind \
				--tool=drd \
				./${NAME} 4 310 200 100

re: fclean all

.PHONY: all clean fclean re val
