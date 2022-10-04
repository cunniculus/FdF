NAME := fdf
SOURCE := main.c

all: $(NAME) 

$(NAME): $(SOURCE)
	gcc -I /usr/local/include/ main.c -L/usr/local/lib -lmlx -lXext -lX11 -o $(NAME)

run: all
	./$(NAME)
