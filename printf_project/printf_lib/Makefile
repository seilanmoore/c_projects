# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 09:34:36 by smoore-a          #+#    #+#              #
#    Updated: 2023/12/19 09:08:22 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

AR = ar rcs

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -O0

LDFLAGS = -L../libft -lft

SRCS = ft_printf.c ft_conversion.c ft_putpointer_fd.c

OBJS = $(SRCS:%.c=%.o)

RM = rm -rf

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re