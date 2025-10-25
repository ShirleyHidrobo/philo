# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shhidrob <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 17:48:43 by shhidrob          #+#    #+#              #
#    Updated: 2025/10/25 18:02:37 by shhidrob         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

ARCHIVE = philo

CC = cc

CFLAGS = -wall -werror -wextra

MAKE_LIB = ar -rcs

SRCS = $()
OBJS = $(SRC:.c=.o)

$(NAME) : $(ARCHIVE)
	$(MAKE_LIB) $(ARCHIVE) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean :
	rm -f $(OBJS) $(ARCHIVE)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
