# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 00:38:01 by smoore-a          #+#    #+#              #
#    Updated: 2025/01/29 22:08:01 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDE = -Iinclude -I/usr/include

HEADER = philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O3 #-g -fsanitize=addres -fno-omit-frame-pointer

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main init check_info simulation monitor logs time error \
	get_set_var sync utils_1 utils_2 cleanup

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all:	$(NAME)

VPATH = src:src/init:src/simulation:src/utils:include

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@
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
	$(MAKE) CFLAGS="-g -O0 -fsanitize=thread" $(NAME)

.PHONY: all clean fclean re nocflag

ifndef VERBOSE
.SILENT:
endif
