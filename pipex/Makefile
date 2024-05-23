# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2024/05/23 20:22:33 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

INCLUDE = -Iinclude -Ilibft/include -I/usr/include

HEADER = pipex.h

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -O0 #-O3

LIBFT_FLAGS = -Llibft -lft

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main

#PARSE_FILE = check_map check_path open_close_file parse_file

#GRAPHICS = init_window init_textures draw_map draw_sections \
	check_moves end_game

#UTILS = cleanup error utils

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC))) \
#	$(addprefix $(SRC_DIR)$(PARSE_FILE_DIR), $(addsuffix .c, $(PARSE_FILE))) \
#	$(addprefix $(SRC_DIR)$(INIT_WINDOW_DIR), $(addsuffix .c, $(GRAPHICS))) \
#	$(addprefix $(SRC_DIR)$(UTILS_DIR), $(addsuffix .c, $(UTILS)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC))) \
#	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSE_FILE))) \
#	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(GRAPHICS))) \
#	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(UTILS)))

VPATH = src:src/graphics:src/parse_map_file:src/utils:include

all:  $(NAME) $(LIBFT)

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(INCLUDE) $^ $(LIBFT_FLAGS) -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make all -C libft
	@echo "$(LIBFT) compiled"

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
	$(MAKE) $(LIBFT)
	$(MAKE) CFLAGS="" $(NAME)

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif