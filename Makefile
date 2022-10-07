NAME := program 
SOURCE := main.c

LIBFT_DIR	:= libft
LIBFT	:= /$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	:= $(LIBFT_DIR)/includes

MLX_DIR	:= minilibx-linux
MLX	:= $(MLX_DIR)/libmlx_Linux.a
MLX_INCLUDES	:= $(MLX_DIR)

CFLAGS	:= -Wall -Wextra -Werror -O3
all: $(NAME) 

$(NAME): $(SOURCE) | $(LIBFT)
	$(CC) $(CFLAGS) -I/usr/local/include -I$(MLX_INCLUDES) -I$(LIBFT_INCLUDES) $< -L/usr/local/lib -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $@
#gcc -I /usr/local/include/ -I$(LIBFT_INCLUDES) main.c -L/usr/local/lib -lmlx -lXext -lX11 -o $(NAME)
	
$(LIBFT):
	make -C $(LIBFT_DIR)

run: all
	./$(NAME)

clean:
	make -C $(LIBFT_DIR) clean

fclean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
