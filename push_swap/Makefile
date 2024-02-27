# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 20:01:41 by smoore-a          #+#    #+#              #
#    Updated: 2024/02/27 10:53:57 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = push_swap

INCLUDE = -I include

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -Llibft -lft

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC =	checks_1 cost divide few_case get_positions \
		init lst_utils_1 lst_utils_2 push_mv push_swap \
		rev_rotate_mv rotate_mv swap_mv moves target \
		checks_2

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))


all:	$(TARGET)

$(TARGET):	$(OBJ_FILES) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $^ -o $@
			@echo "$(TARGET) compiled"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
				@echo "$< compiled"

$(LIBFT):
			make -C libft
			make bonus -C libft
			@echo "$(LIBFT) compiled"

clean:
		$(RM) $(OBJ_DIR)
		@echo "Object files removed"
		make clean -C libft
		@echo "Libft object files removed"

fclean:	clean
		$(RM) $(TARGET)
		@echo "$(TARGET) removed"
		$(RM) $(LIBFT)
		@echo "$(LIBFT) removed"

re:	fclean all

.PHONY:	all clean fclean re

ifndef VERBOSE
.SILENT:
endif