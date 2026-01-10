# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 15:31:32 by shhidrob          #+#    #+#              #
#    Updated: 2026/01/10 21:43:34 by shhidrob         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/

SRC = main.c actions.c builders.c checkings.c timing.c utilities.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
