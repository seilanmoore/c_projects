# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 20:08:31 by smoore-a          #+#    #+#              #
#    Updated: 2023/12/20 10:02:00 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		=	\033[0;32m
RED			=	\033[0;31m
YELLOW		=	\033[1;33m
RESET		=	\033[0m

NAME		= 	libftprintf.a
INCLUDE		=	include
SRC_DIR		= 	src/
OBJ_DIR		= 	obj/
CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -g -I
RM			= 	rm -rf
AR			= 	ar rcs

SRC_FILES	=	ft_printf ft_conversion ft_hex_address ft_uitoa\
				ft_puthex_fd
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:			$(NAME)

$(NAME):		$(OBJ)
				@echo "$(YELLOW)Compiling the libft library...$(RESET)"
				@make -C libft
				@cp libft/libft.a .
				@echo "$(YELLOW)Copying libft.a to the current directory...$(RESET)"
				@mv libft.a $(NAME)
				@echo "$(YELLOW)Renaming libft.a to $(NAME)...$(RESET)"
				@$(AR) $(NAME) $(OBJ)
				@echo "$(GREEN)Creating the final library $(NAME)...$(RESET)"

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c | $(OBJF)
				@echo "$(YELLOW)Compiling $<...$(RESET)"
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
				@echo "$(YELLOW)Creating $(OBJ_DIR) directory...$(RESET)"
				@mkdir -p $(OBJ_DIR)

clean:
				@echo "$(RED)Cleaning up object files...$(RESET)"
				@$(RM) $(OBJ_DIR)
				@echo "$(RED)Calling clean in libft...$(RESET)"
				@make clean -C libft

fclean:			clean
				@echo "$(RED)Cleaning up $(NAME)...$(RESET)"
				@$(RM) $(NAME)
				@echo "$(RED)Removing libft/libft.a...$(RESET)"
				@$(RM) libft/libft.a

re:				fclean all

.PHONY:			all clean fclean re