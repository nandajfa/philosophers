# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 22:45:52 by jefernan          #+#    #+#              #
#    Updated: 2022/12/04 22:50:18 by jefernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
PTHREAD = -pthread
INCLUDES = -I./includes
RM = rm -rf

GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
WHT			:=	\033[1;37m
EOC			:=	\033[1;0m

vpath %.c src

SRCS =	philo.c check.c utils.c simulation.c verify.c init.c time.c

OBJ_DIR = ./objs
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	@ echo "Compiling... "
	@ $(CC) $(CFLAGS) $(OBJECTS) $(PTHREAD) $(INCLUDES) -o $@
	@ echo "$(GREEN)"
	@ echo "=========================="
	@ echo "  Compiled successfully!"
	@ echo "=========================="
	@ echo "$(EOC)"

$(OBJ_DIR)/%.o: %.c
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

valgrind:	
			@echo "$(WHT)Removing old log.$(EOC)"
			@rm -f valgrind-out.txt
			@echo "$(WHT)Old log removed.$(EOC)"
			@echo "$(WHT)Executing Valgrind.$(EOC)"
			@valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt \
			./$(NAME) 5 800 200 200 5 
			@echo "$(GREEN)Valgrind-log created.$(EOC)"

clean:
	@ $(RM) $(OBJ_DIR)
	@ echo "Objects removed."

fclean:
	@ $(RM) $(OBJ_DIR)
	@ $(RM) $(NAME)
	@ echo "Program has been cleaned!"

re: fclean all

PHONY:	all clean fclean re