# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2024/05/19 13:18:01 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

MLX = mlx_linux/libmlx_Linux.a

INCLUDE = -Iinclude -Ilibft/include -I/usr/include -Imlx_linux

HEADER = include/so_long.h

CC = gcc -g

CFLAGS = -Wall -Werror -Wextra -O0 #-O3

LIBFT_FLAGS = -Llibft -lft

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main

PARSE_FILE_DIR = parse_map_file/

PARSE_FILE = check_map check_path init_map open_close_file parse_file

INIT_WINDOW_DIR = init_window/

INIT_WINDOW = init_window

UTILS_DIR = utils/

UTILS = cleanup utils

#SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC))) \
	$(addprefix $(SRC_DIR)$(PARSE_FILE_DIR), $(addsuffix .c, $(PARSE_FILE))) \
	$(addprefix $(SRC_DIR)$(INIT_WINDOW_DIR), $(addsuffix .c, $(INIT_WINDOW))) \
	$(addprefix $(SRC_DIR)$(UTILS_DIR), $(addsuffix .c, $(UTILS))) \

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')

#OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSE_FILE))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(INIT_WINDOW))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(UTILS))) \

OBJ_FILES = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

all: $(NAME) $(MLX) $(LIBFT)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS_USE) $(INCLUDE) $^ $(MLX_FLAGS) $(LIBFT_FLAGS) -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_USE) $(INCLUDE) -c $< -o $@
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

noflag:
	$(MAKE) CFLAGS_USE="" all

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif