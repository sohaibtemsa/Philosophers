# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 16:39:18 by stemsama          #+#    #+#              #
#    Updated: 2023/07/06 14:33:58 by stemsama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra

SRC = tools1.c tools2.c tools3.c main.c parsing.c 


OBJECT = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECT) philo.h
	$(CC) $(FLAGS) $(OBJECT) -o $(NAME)

%.o:%.c philo.h
	$(CC) $(FLAGS) -c $< -o $@ 

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all 

.PHONY: clean fclean re all
