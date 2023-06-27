# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samy <samy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 11:24:14 by samy              #+#    #+#              #
#    Updated: 2023/06/27 21:58:08 by samy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PRINTF = 	ft_printf.c\
		ft_printf_utils.c\
		ft_printf_utils_print.c

GNL = 	get_next_line.c\
		get_next_line_utils.c

SRC = 	ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_strlcpy.c\
		ft_memmove.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strrncmp.c\
		ft_strcmp.c\
		ft_free_split.c\
		ft_nb_split.c\
		ft_str_is_numeric.c\
		ft_is_quote.c\
		ft_is_space.c\
		ft_isempty.c\
		ft_join_and_assign.c

BONUS = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c

SRCS = $(SRC) $(PRINTF) $(GNL)

SRCS_DIR = srcs
OBJS_DIR = objs

OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})
OBJS_BONUS = $(addprefix ${OBJS_DIR}/, ${BONUS:%.c=%.o})
CC			=	cc

        # Colors #
YELLOW = \033[1;33m
CYAN = \033[1;36m
GREEN	= \033[0;32m
RESET = \033[0m
_SUCCESS        =  [$(GREEN)SUCCESS$(RESET)]
_INFO           =  [$(YELLOW)INFO$(RESET)]

FLAG = -Wall -Wextra -Werror
ARRCS		=	ar rcs
RM		= rm -rf

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@cc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(ARRCS) $(NAME) $^
	@echo "$(_SUCCESS) $(NAME) ready."

all: $(NAME) bonus

bonus: $(OBJS_BONUS)
	@$(ARRCS) $(NAME) $^
	@echo "$(_SUCCESS) $(NAME) bonus ready."

clean:
	@${RM} -r ${OBJS_DIR}
	@echo "$(_INFO) $(NAME) objects removed."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(_INFO) $(NAME) removed."

re: fclean all

.PHONY:			all clean fclean re bonus