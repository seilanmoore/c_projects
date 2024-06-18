# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 22:42:26 by smoore-a          #+#    #+#              #
#    Updated: 2024/06/18 12:13:03 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDE = -Iinclude -I/usr/include

HEADER = philo.h

CC = clang

CFLAGS = -pthread -Wall -Werror -Wextra -g -O0 #-O3

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main \
	check init \
	simulation actions\
	error utils cleanup time_related

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all:	$(NAME)

VPATH = src:src/init:src/simulation:src/utils:include

$(NAME): $(OBJ_FILES)
	$(CC) $(INCLUDE) $^ -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

nocflag:
	$(MAKE) CFLAGS="-g -O0 -pthread" $(NAME)

.PHONY: all clean fclean re nocflag

ifndef VERBOSE
.SILENT:
endif