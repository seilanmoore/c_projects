# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 09:34:36 by smoore-a          #+#    #+#              #
#    Updated: 2023/12/19 15:15:10 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft/libft.a

AR = ar rcs

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -O0

SRCS = 	ft_printf.c ft_conversion.c ft_putpointer_fd.c ft_uitoa.c\
		ft_puthex_fd.c

OBJS = $(SRCS:%.c=%.o)

RM = rm -rf

$(LIBFT):
    $(MAKE) -C libft/

$(NAME): $(OBJS) $(LIBFT)
	$(AR) $(NAME) $(OBJS) libft/*.o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

all: 	$(NAME)

.PHONY: all clean fclean re