# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/31 10:01:39 by cmalt             #+#    #+#              #
#    Updated: 2021/01/01 06:00:13 by cmalt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo_one

CLANG = 	clang -Wall -Werror -Wextra

SRC =		philo.c \
			init/create_list_philo.c \
			init/create_mutex.c \
			init/create_pthreads.c \
			init/free.c \
			init/parse_args.c \
			pthreads/create_monitors_pthreads.c \
			pthreads/philo_doing_func.c \
			pthreads/print_funcs.c \
			pthreads/pthreads_func.c \
			pthreads/utils_func.c

OBJ =		$(SRC:.c=.o)

HEAD =		headers/

all:		$(NAME)

%.o:		%.c
	$(CLANG) -I $(HEAD) -c $< -o $@

$(NAME):	$(OBJ)
	$(CLANG) $^ -lpthread -I $(HEAD) -o $@

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all