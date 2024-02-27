# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2024/02/27 20:50:44 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCLUDE = -I include

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -Llibft -lft

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC =	

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))


all: $(NAME)

$(NAME):	$(OBJ_FILES) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $^ -o $@
			@echo "$(NAME) compiled"

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
		$(RM) $(NAME)
		@echo "$(NAME) removed"
		$(RM) $(LIBFT)
		@echo "$(LIBFT) removed"

re: fclean all

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif