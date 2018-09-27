# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/17 17:44:05 by ikotvits          #+#    #+#              #
#    Updated: 2018/07/17 17:44:06 by ikotvits         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm

LIB_DIR = libft/

SRCS = fdf.c get_map.c map_modify.c mouse.c draw_map.c fdf_trash.c

DIR = fdf_dir/

SRC = $(addprefix $(DIR), $(SRCS))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(addprefix $(DIR), fdf.h)
	@ make -C $(LIB_DIR)
	@ gcc $(MLX_FLAGS) $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft
	@ tput setaf 3; echo "Binary file has been created"

%.o: %.c
	@ gcc $(FLAGS) -o $@ -c $< -I $(DIR)

clean:
	@ rm -f $(OBJ)
	@ make -C ./libft clean
	@ tput setaf 4; echo All object files have been deleted

fclean: clean
	@ rm -f $(NAME)
	@ make -C ./libft fclean
	@ tput setaf 5; echo Binary file has been deleted

re: fclean all

.PHONY: fclean clean all re