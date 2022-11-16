# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 22:45:52 by jefernan          #+#    #+#              #
#    Updated: 2022/11/17 00:40:09 by jefernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
INCLUDES = -I./includes
RM = rm -rf

vpath %.c src

SRCS =	philo.c check.c utils.c simulation.c verify.c init.c

OBJ_DIR = ./objs
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	@ echo "Compiling... "
	@ $(CC) $(CFLAGS) $(OBJECTS) $(PTHREAD) $(INCLUDES) -o $@
	@ echo "\033[1;32m"
	@ echo "=========================="
	@ echo "  Compiled successfully!"
	@ echo "=========================="
	@ echo "\033[0m"

$(OBJ_DIR)/%.o: %.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

leak:	all
		valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200 5

clean:
	@ $(RM) $(OBJ_DIR)
	@ echo "Objects removed."

fclean:
	@ $(RM) $(OBJ_DIR)
	@ $(RM) $(NAME)
	@ echo "Program has been cleaned!"

re: fclean all

PHONY:	all clean fclean re