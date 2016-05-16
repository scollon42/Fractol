# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollon <scollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/01 10:19:30 by scollon           #+#    #+#              #
#    Updated: 2016/01/29 09:08:48 by scollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
INC_LIBFT_PATH = ./libft/includes/
LIB_PATH = ./libft/
MLX_PATH = ./mlx

NAME = fractol
CC = gcc
CFGLAGS = -Werror -Wextra -Wall -o2
MLX = -L$(MLX_PATH) -I$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

SRC_NAME = main.c draw.c env.c fractals.c hook.c event.c exit.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft.a

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
INC_LIBFT = $(addprefix -I,$(INC_LIBFT_PATH))
LIB = $(LIB_PATH)$(LIB_NAME)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft re
	make -C mlx re
	$(CC) $(CFLAGS) $(MLX) $(LIB) $(INC_LIBFT) $(INC) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC_LIBFT) $(INC) -o $@ -c $<

.PHONY: clean fclean re check fclean_libft clean_libft

clean:
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

clean_libft:
	make -C libft clean

fclean: clean fclean_libft
	rm -f $(NAME)

fclean_libft:
	make -C libft fclean

re: fclean all

check:
	@ls libft | grep -q libft.a && echo "\033[1mLIBFT\033[0m      [\033[32mOK\033[0m]" \
							    || echo "\033[1mLIBFT\033[0m      [\033[31mKO\033[0m]"
	@ls mlx | grep -q libmlx.a && echo "\033[1mMLX\033[0m        [\033[32mOK\033[0m]" \
							   || echo "\033[1mMLX\0330m [\033[31mKO\033[0m]"
	@ls | grep -q -U fractol && echo "\033[1mFRACTOL\033[0m    [\033[32mOK\033[0m]" \
							 || echo "\033[1mFRACTOL\033[0m    [\033[31mKO\033[0m]"
	@ls | grep -q auteur && echo "\033[1mAUTEUR\033[0m     [\033[32mOK\033[0m]" \
					     || echo "\033[1mAUTEUR\033[0m     [\033[31mKO\033[0m]"
	@norminette src/ includes/ libft/src/ libft/includes/ | grep -B 1 Error && \
		echo "\033[1mNORMINETTE\033[0m [\033[31mKO\033[0m]" \
	 || echo "\033[1mNORMINETTE\033[0m [\033[32mOK\033[0m]"
