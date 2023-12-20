# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:26:15 by smoore-a          #+#    #+#              #
#    Updated: 2023/12/20 10:02:13 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
INCLUDE		=	../include
SRCS_DIR 	=	src/
OBJS_DIR	=	obj/
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -I
RM			=	rm -f
AR			=	ar rcs

SRC_FILES	=	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint\
				ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove\
				ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr\
				ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr\
				ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin\
				ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri\
				ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJSF		=	.cache_exists

all:			$(NAME)
	
$(NAME):		$(OBJS)
				@$(AR) $(NAME) $(OBJS)
				@ranlib $(NAME)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c | $(OBJSF)
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJSF):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)$(SRCS_DIR)

clean:
				@$(RM) -rf $(OBJS_DIR)
				@$(RM) -f $(OBJSF)

fclean:			clean
				@$(RM) -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re