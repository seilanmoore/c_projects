# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2024/03/11 09:29:24 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

MLX = mlx_linux/libmlx_Linux.a

INCLUDE = -Iinclude -Ilibft/include -I/usr/include -Imlx_linux

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -O0 #-O3

LIBFT_FLAGS = -Llibft -lft

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = so_long handle_map check_map ft_mlx

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))


all: $(NAME) $(MLX) $(LIBFT)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(MLX_FLAGS) $(LIBFT_FLAGS) -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make all bonus -C libft
	@echo "$(LIBFT) compiled"

$(MLX):
	@make all -C mlx_linux
	@echo "$(MLX) compiled"

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"
	@make clean -C libft
	@echo "Libft object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"
	$(RM) $(LIBFT)
	@echo "$(LIBFT) removed"
	@make clean -C mlx_linux
	@echo "Mlx cleaned"

re: fclean all

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif