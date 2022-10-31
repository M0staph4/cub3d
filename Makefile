NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g
SRC = cub3d.c inc/gnl/get_next_line.c inc/gnl/get_next_line_utils.c render.c \
	map.c raycasting.c moves.c texture.c map_tools.c
LIB = libft.a
INC = -lmlx -framework OpenGL -framework AppKit 

# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m'
_BOLD=$'\x1b[1m'

# Colors
_RED=$'\x1b[31m'
_GREEN=$'\x1b[32m'
_CYAN=$'\x1b[36m'


all : $(NAME)

$(LIB):
	@echo "${_BOLD}${_CYAN}---------Libft Compilation---------${_END}"
	make -C inc/libft --silent
	cp inc/libft/libft.a ./

$(NAME): $(SRC) $(LIB)
	@echo "${_BOLD}${_GREEN}---------Cub3D Compilation---------${_END}"
	$(CC) $(CFLAGS)  $(SRC) $(INC) -o $(NAME) $(LIB)

clean:
	@echo "${_BOLD}${_RED}---------Cleaning Objects---------${_END}"
	rm -f *.o
	rm -f inc/libft/*.o
fclean: clean
	@echo "${_BOLD}${_RED}---------Deleting---------${_END}"
	rm -f cub3d
	rm -f $(LIBFT_A)
	rm -f inc/libft/libft.a 
	rm -f libft.a

re : fclean all
