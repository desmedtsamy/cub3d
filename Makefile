# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samy <samy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 11:51:56 by sde-smed          #+#    #+#              #
#    Updated: 2023/07/02 00:38:40 by samy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
LIB		=	-L ./libft -lft -L /usr/local/include -lmlx -framework OpenGL -framework AppKit
SRCS	= 	main.c\
			parsing.c\
			utils.c\
			get_data.c\
			parsing_map.c\
			parsing_map_utils.c\
			get_texture.c\
			minimap.c\
			moves.c\
			init.c

LIBFT	= libft/

SRCS_DIR = srcs
OBJS_DIR = objs
OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})
OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM		= rm -rf

        # Colors #
YELLOW = \033[1;33m
CYAN = \033[1;36m
GREEN	= \033[0;32m
RESET = \033[0m
_SUCCESS        =       [$(GREEN)SUCCESS$(RESET)]
_INFO           =       [$(YELLOW)INFO$(RESET)]

all: $(NAME)

$(NAME): $(OBJS)
	@make all -C $(LIBFT)
	@cc $(FLAGS) $(INCLUDES) $(OBJS) $(LIB) -o $(NAME)
	@echo "$(_SUCCESS) $(NAME) ready."

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@cc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		@make -C $(LIBFT) clean
		@${RM} -r ${OBJS_DIR}
		@echo "$(_INFO) $(NAME) objects folder removed."

fclean:
		@make -C $(LIBFT) fclean
		@${RM} -r ${OBJS_DIR}
		@echo "$(_INFO) $(NAME) objects removed."
		@${RM} ${NAME}
		@echo "$(_INFO) $(NAME) removed."

re: fclean all

.PHONY:			all clean fclean re