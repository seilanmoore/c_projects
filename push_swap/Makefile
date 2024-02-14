# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 20:01:41 by smoore-a          #+#    #+#              #
#    Updated: 2024/02/14 21:36:37 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=		push_swap
INCLUDE				=		include
SRC_DIR				=		src/
OBJ_DIR				=		obj/
CC					=		cc
CFLAGS				=		-Wall -Werror -Wextra -g -I
RM					=		rm -rf
AR					=		ar rcs

SRC_FILES			=		checks cost few_case get_positions init lst_utils_1\
							lst_utils_2 push_mv push_swap rev_rotate_mv\
							rotate_mv swap_mv moves target
SRC					=		$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ					=		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF				=		.cache_exists

all:							$(NAME)

$(NAME):						$(OBJ)
								@echo "Compiling the libft library..."
								@make -C libft
								@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -Llibft -lft -o $@

$(OBJ_DIR)%.o:					$(SRC_DIR)%.c | $(OBJF)
								@echo "Compiling $<..."
								@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
								@echo "Creating $(OBJ_DIR) directory..."
								@mkdir -p $(OBJ_DIR)

clean:
								@echo "Cleaning up object files..."
								@$(RM) $(OBJ_DIR)
								@echo "Calling clean in libft..."
								@make clean -C libft

fclean:							clean
								@echo "Cleaning up $(NAME)..."
								@$(RM) $(NAME)
								@echo "Removing libft/libft.a..."
								@$(RM) libft/libft.a

re:								fclean all

.PHONY:							all clean fclean re