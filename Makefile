NAME			:= program 
SOURCE			:= read_file.c
OBJ				:= read_file.o

LIBFT_DIR		:= libft
LIBFT			:= /$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	:= $(LIBFT_DIR)/includes

MLX_DIR			:= minilibx-linux
MLX				:= $(MLX_DIR)/libmlx_Linux.a
MLX_INCLUDES	:= $(MLX_DIR)

INCLUDES 		:= -I/usr/local/include -I$(MLX_INCLUDES) -I$(LIBFT_INCLUDES)
LIB_PATHS		:= -L/usr/local/lib -L$(MLX_DIR) -L$(LIBFT_DIR)
LIBS			:= -lft -lmlx -lmlx_Linux -lXext -lX11 -lm 

MLX_DIR_MAC		:= minilibx_macos
LIBS_MAC		:= -lft -lmlx -lmlx -lm
FRAMEWORKS		:= -framework OpenGL -framework AppKit

CFLAGS			:= -Wall -Wextra -Werror -O3

all: $(NAME) 

	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIB_PATHS) $(LIBS) -o $@
#$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIB_PATHS) $(LIBS) -o $@

$(OBJ): $(SOURCE) | $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@
#$(CC) $(CFLAGS) $(INCLUDES) $< $(LIB_PATHS) $(LIBS) -c -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

run: all
	./$(NAME)

mac: $(OBJ) 
	$(CC) $(CFLAGS) $^ $(LIB_PATHS) $(LIBS) $(FRAMEWORKS) -o $@

debug:
	$(CC) $(CFLAGS) -g3 $(INCLUDES) $(SOURCE) -c -o $(OBJ)
	$(CC) $(CFLAGS) -g3 $(OBJ) $(LIB_PATHS) $(LIBS) -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

man:
	man /usr/local/man/man3/*
clean:
	rm -f *.o
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
