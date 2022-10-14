NAME			:=	program
SOURCE			:=	fdf_utils.c\
					rotation.c\
					scale.c\
					translate.c\
					read_file.c\
					bresenham.c\
					draw_line_bresenham.c

OBJ				:= $(SOURCE:.c=.o)

LIBFT_DIR		:= libft
LIBFT			:= /$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	:= $(LIBFT_DIR)/includes

MLX_DIR			:= minilibx-linux
MLX				:= $(MLX_DIR)/libmlx_Linux.a
MLX_INCLUDES	:= $(MLX_DIR)

INCLUDES 		:= -I/usr/local/include -I$(MLX_INCLUDES) -I$(LIBFT_INCLUDES) -I.
LIB_PATHS		:= -L/usr/local/lib -L$(MLX_DIR) -L$(LIBFT_DIR)
LIBS			:= -lft -lmlx -lmlx_Linux -lXext -lX11 -lm

CFLAGS			:= -Wall -Wextra -Werror -O3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIB_PATHS) $(LIBS) -o $@

$(OBJ): $(SOURCE) | $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCE) -c

$(LIBFT):
	make -C $(LIBFT_DIR)

run: all
	./$(NAME) test_maps/42.fdf

debug:
	$(CC) $(CFLAGS) -g3 $(INCLUDES) $(SOURCE) -c
	$(CC) $(CFLAGS) -g3 $(OBJ) $(LIB_PATHS) $(LIBS) -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) test_maps/42.fdf

man:
	man /usr/local/man/man3/*
clean:
	rm -f *.o
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
