# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:26:15 by smoore-a          #+#    #+#              #
#    Updated: 2024/02/27 13:07:58 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

INCLUDE = -I ../include

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC =	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
		ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove \
		ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr \
		ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr \
		ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin \
		ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
		ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

BONUS_SRC =	ft_lstnew_bonus ft_lstadd_front_bonus \
			ft_lstsize_bonus ft_lstlast_bonus \
			ft_lstadd_back_bonus ft_lstdelone_bonus \
			ft_lstclear_bonus ft_lstiter_bonus \
			ft_lstmap_bonus

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

BONUS_SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(BONUS_SRC)))

BONUS_OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BONUS_SRC)))


all:	$(NAME)

$(NAME):	$(OBJ_FILES)
			ar rcs $(NAME) $(OBJ_FILES)
			@echo "$(NAME) compiled"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 
				@echo "$< compiled"

bonus:	$(BONUS_OBJ_FILES)
		ar rcs $(NAME) $(BONUS_OBJ_FILES)
		@echo "Bonus compiled"

clean:
		$(RM) $(OBJ_DIR)
		@echo "Object files removed"

fclean:	clean
		$(RM) $(NAME)
		@echo "$(NAME) removed"

re:	fclean all

.PHONY:	all clean fclean re bonus

ifndef VERBOSE
.SILENT:
endif