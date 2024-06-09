# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 22:09:52 by smoore-a          #+#    #+#              #
#    Updated: 2024/06/09 11:38:07 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex_bonus

INCLUDE = -Iinclude -I../libft/include -I/usr/include

HEADER = pipex_bonus.h

CC = clang

CFLAGS = -g -Wall -Werror -Wextra -O0 #-O3

LIBFT_FLAGS = -L../libft -lft

LIBFT = ../libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main init

UTILS = cleanup error

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(UTILS)))

VPATH = src:src/utils:include

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(INCLUDE) $^ $(LIBFT_FLAGS) -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make all -C ../libft
	@echo "$(LIBFT) compiled"

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"
	$(RM) $(LIBFT)
	@echo "$(LIBFT) removed"

re: fclean all

nocflag:
	$(MAKE) $(LIBFT)
	$(MAKE) CFLAGS="" $(NAME)

.PHONY: all clean fclean re nocflag

ifndef VERBOSE
.SILENT:
endif