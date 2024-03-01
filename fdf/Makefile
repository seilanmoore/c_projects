# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2024/03/01 22:32:56 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

MLX = mlx/libmlx.a

INCLUDE = -Iinclude -Ilibft/include -Imlx

CC = gcc

CPPFLAGS = -g -Wall -Werror -Wextra

LIBFT_FLAGS = -Llibft -lft

MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 \
	-framework OpenGL -framework AppKit

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = fdf

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))


all: $(NAME) $(MLX) $(LIBFT)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@ $(LIBFT_FLAGS) $(MLX_FLAGS)
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make all bonus -C libft
	@echo "$(LIBFT) compiled"

$(MLX):
	@make all -C mlx
	@echo "$(MLX) compiled"

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"
	make clean -C libft
	@echo "Libft object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"
	$(RM) $(LIBFT)
	@echo "$(LIBFT) removed"

re: fclean all

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif