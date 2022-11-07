# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 22:23:58 by mmoutawa          #+#    #+#              #
#    Updated: 2022/11/04 12:49:59 by mmoutawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = cub3d.c inc/gnl/get_next_line.c inc/gnl/get_next_line_utils.c Render.c \
	Map.c Raycasting.c Moves.c Textures.c Player.c MapTools.c Maths.c \
	MapTools2.c MapTools3.c
LIB = libft.a
INC = -lmlx -framework OpenGL -framework AppKit 

all : $(NAME)

$(LIB):
	@echo "---------Libft Compilation---------"
	make -C inc/libft --silent
	cp inc/libft/libft.a ./

$(NAME): $(SRC) $(LIB)
	@echo "---------Cub3D Compilation---------"
	$(CC) $(CFLAGS)  $(SRC) $(INC) -o $(NAME) $(LIB)

clean:
	@echo "---------Cleaning Objects---------"
	rm -f *.o
	rm -f inc/libft/*.o
	rm -f inc/gnl/*.o
fclean: clean
	@echo "---------Deleting---------"
	rm -f cub3d
	rm -f $(LIBFT_A)
	rm -f inc/libft/libft.a 
	rm -f libft.a

re : fclean all
