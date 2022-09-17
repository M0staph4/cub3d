NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
SRCS = cub3d.c inc/gnl/get_next_line.c inc/gnl/get_next_line_utils.c render.c
INC = -lmlx -framework OpenGL -framework AppKit 

LIBFT_A = libft.a
LIBF_DIR = inc/libft/
LIBFT  = $(addprefix $(LIBF_DIR), $(LIBFT_A))

OBJ = $(SRCS:.c=.o)

%.o: %.c
	$(CC)  $(CFLAGS)  -Imlx -c $< -o $@
$(NAME): $(OBJ)
	make -C $(LIBF_DIR)
	cp inc/libft/libft.a .
	$(CC) $(FLAGS) $(OBJ) $(LIBFT)  $(INC) -o $(NAME)

all : $(NAME) 

clean :
	rm -f ${OBJ}
	rm -f inc/libft/*.o
fclean : clean
	rm -f cub3d
	rm -f $(LIBFT_A)
	rm -f inc/libft/libft.a 
re : fclean all
