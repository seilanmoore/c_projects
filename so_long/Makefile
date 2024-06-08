# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2024/06/08 14:27:41 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

INCLUDE = -Iinclude -Ilibft/include -I/usr/include -Iminilibx-linux

HEADER = so_long.h

CC = clang

CFLAGS = -Wall -Werror -Wextra -O3 #-O0

LIBFT_FLAGS = -Llibft -lft

MLX_FLAGS = -Lminilibx-linux -lmlx_Linux \
	-L/usr/include/../lib -lXext -lX11 -lm -lbsd

LIBFT = libft/libft.a

MLX = minilibx-linux/libmlx_Linux.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main

PARSE_FILE = check_map check_path open_close_file parse_file

GRAPHICS = init_window init_textures draw_map draw_sections \
	check_moves end_game

UTILS = cleanup error utils

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC))) \
	$(addprefix $(SRC_DIR)$(PARSE_FILE_DIR), $(addsuffix .c, $(PARSE_FILE))) \
	$(addprefix $(SRC_DIR)$(INIT_WINDOW_DIR), $(addsuffix .c, $(GRAPHICS))) \
	$(addprefix $(SRC_DIR)$(UTILS_DIR), $(addsuffix .c, $(UTILS)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSE_FILE))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(GRAPHICS))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(UTILS)))

VPATH = src:src/graphics:src/parse_map_file:src/utils:include

all: $(NAME) $(LIBFT) $(MLX)

$(NAME): $(MLX) $(LIBFT) $(OBJ_FILES)
	$(CC) $(INCLUDE) $^ $(MLX_FLAGS) $(LIBFT_FLAGS) -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make all -C libft
	@echo "$(LIBFT) compiled"

$(MLX):
	@make all -C minilibx-linux
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
	@make clean -C minilibx-linux
	@echo "$(MLX) compiled"

re: fclean all

nocflag:
	$(MAKE) $(MLX) $(LIBFT)
	$(MAKE) CFLAGS="" $(NAME)

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif