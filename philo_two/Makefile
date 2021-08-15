# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/31 10:01:39 by cmalt             #+#    #+#              #
#    Updated: 2020/12/31 11:35:56 by cmalt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo_two

CLANG = 	clang -Wall -Werror -Wextra

SRC =		philo.c \
			init/free.c \
			init/parse_args.c \
			init/create_pthreads.c \
			init/create_semaphore.c \
			init/create_list_philo.c \
			pthreads/create_monitors_pthreads.c \
			pthreads/philo_doing_func.c \
			pthreads/pthreads_func.c \
			pthreads/print_funcs.c \
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