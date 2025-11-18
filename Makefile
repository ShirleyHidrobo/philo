# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 15:31:32 by shhidrob          #+#    #+#              #
#    Updated: 2025/11/18 17:51:32 by shhidrob         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc

LINKFLAGS = -pthread

CFLAGS =	-Wall -Wextra -Werror \
			-g3 -gdwarf-3 \
			-O0 \
			-pthread \
			-Iinc.-

# 			-fsanitize=thread \

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR     = inc/

SRC =	main.c \
 		  actions.c \
 		  builders.c \
 		  checkings.c \
 		  timing.c \
 		  utilities.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@rmdir $(OBJ_DIR) || true

fclean: clean
	@rm -f $(NAME)

re: fclean all

valgrind: re
	valgrind --trace-children=yes --leak-check=full ./$(NAME) 10 800 200 200

.PHONY: all clean fclean re valgrind


# NAME    = philo

# CC      = cc
# CFLAGS  = -Wall -Wextra -Werror -pthread -fsanitize=thread -g3 -O0 -Iinc

# SRC_DIR     = src/
# OBJ_DIR     = obj/
# INC_DIR     = inc/

# SRC    = main.c \
# 		  actions.c \
# 		  builders.c \
# 		  checkings.c \
# 		  timing.c \
# 		  utilities.c \

# SRCS = $(addprefix $(SRC_DIR), $(SRC))

# OBJS    = $(SRC:.c=.o)
# OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

# $(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
# 	mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# all: $(NAME)

# $(NAME): $(OBJECTS)
# 	@echo "Compiling $(NAME)..."
# 	$(CC) $(CFLAGS) $(OBJECTS) -I$(INC_DIR) -o $(NAME)

# clean:
# 	@echo "Cleaning object files..."
# 	rm -f $(OBJS)

# fclean: clean
# 	@echo "Cleaning executable..."
# 	rm -f $(NAME)

# re: fclean all

# run: all
# 	./$(NAME)

# .PHONY: all clean fclean re run
