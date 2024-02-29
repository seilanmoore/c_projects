# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 20:08:31 by smoore-a          #+#    #+#              #
#    Updated: 2024/02/29 23:02:07 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
INCLUDE = include
SRC_DIR = src/
OBJ_DIR = obj/
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I
RM = rm -rf
AR = ar rcs
SRC_FILES =	ft_printf ft_conversion ft_hex_address ft_uitoa \
			ft_puthex_fd ft_printf_itoa ft_printf_utils
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME):	$(OBJ)
			@make all -C libft
			@echo "Libft.a compiled"
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(AR) $(NAME) $(OBJ)
			@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
				@echo "$< compiled"

clean:
		@$(RM) $(OBJ_DIR)
		@echo "Object files removed"
		@make clean -C libft
		@echo "Libft clean called"

fclean:	clean
		@$(RM) $(NAME)
		@echo "$(NAME) removed"
		@$(RM) libft/libft.a
		@echo "Libft.a removed"

re: fclean all

.PHONY: all clean fclean re