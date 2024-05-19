# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:26:15 by smoore-a          #+#    #+#              #
#    Updated: 2024/05/19 17:03:48 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

INCLUDE = -Iinclude

HEADER = include/

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

BONUS = bonus/

PRINTF = printf/

GNL = get_next_line/

SRC = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
	ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove \
	ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr \
	ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr \
	ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin \
	ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \

BONUS_SRC = ft_lstnew_bonus ft_lstadd_front_bonus \
	ft_lstsize_bonus ft_lstlast_bonus \
	ft_lstadd_back_bonus ft_lstdelone_bonus \
	ft_lstclear_bonus ft_lstiter_bonus \
	ft_lstmap_bonus

PRINTF_SRC = ft_printf ft_conversion ft_hex_address ft_puthex_fd \
	ft_uitoa ft_printf_itoa ft_printf_utils

GNL_SRC = get_next_line get_next_line_utils

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

BONUS_SRC_F = $(addprefix $(BONUS)$(SRC_DIR), $(addsuffix .c, $(BONUS_SRC)))

BONUS_OBJ_F = $(addprefix $(BONUS)$(OBJ_DIR), $(addsuffix .o, $(BONUS_SRC)))

PRINTF_SRC_F = $(addprefix $(PRINTF)$(SRC_DIR), $(addsuffix .c, $(PRINTF_SRC)))

PRINTF_OBJ_F = $(addprefix $(PRINTF)$(OBJ_DIR), $(addsuffix .o, $(PRINTF_SRC)))

GNL_SRC_F = $(addprefix $(GNL)$(SRC_DIR), $(addsuffix .c, $(GNL_SRC)))

GNL_OBJ_F = $(addprefix $(GNL)$(OBJ_DIR), $(addsuffix .o, $(GNL_SRC)))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(PRINTF_OBJ_F) $(GNL_OBJ_F)
	ar rcs $@ $^
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)libft.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 
	@echo "$< compiled"

bonusts = .bonus_timestamp

bonus: $(bonusts)

$(bonusts): $(BONUS_OBJ_F)
	@touch $@
	ar rcs $(NAME) $^
	@echo "Bonus compiled"

$(BONUS)$(OBJ_DIR)%.o:	$(BONUS)$(SRC_DIR)%.c $(HEADER)libft.h
	@mkdir -p $(BONUS)$(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(PRINTF)$(OBJ_DIR)%.o:	$(PRINTF)$(SRC_DIR)%.c $(HEADER)ft_printf.h
	@mkdir -p $(PRINTF)$(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(GNL)$(OBJ_DIR)%.o: $(GNL)$(SRC_DIR)%.c $(HEADER)get_next_line.h
	@mkdir -p $(GNL)$(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

clean:
	$(RM) $(OBJ_DIR) $(PRINTF)$(OBJ_DIR) $(GNL)$(OBJ_DIR) $(BONUS)$(OBJ_DIR) $(bonusts)
	@echo "Object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re bonus

ifndef VERBOSE
.SILENT:
endif