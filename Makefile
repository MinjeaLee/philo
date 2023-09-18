# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 11:21:18 by mi                #+#    #+#              #
#    Updated: 2023/09/18 02:57:55 by mi               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
HEADER = ./includes

SRCS =	./src/philo.c \
		./src/utils.c \
		./src/init.c \
		./src/status.c \
		./src/time.c	\
		./src/monitor.c 
	
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) $< -o $@ -c -I$(HEADER)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -g -o $@ $^
	@echo "\033[32m[Success] \033[0m$@ is created"
re: fclean all

clean:
	@rm -f $(OBJS) 
	@echo "\033[31m[Success] \033[0m$(NAME) clean"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m[Success] \033[0m$(NAME) fclean"

.PHONY: all clean fclean re