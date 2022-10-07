NAME				:= libft.a
INCLUDES			= includes

LIBFT_DIR			:= libsrc
OBJDIR				:= obj
LIBFT_SRC_LIST		:= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
					ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_toupper.c\
					ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
					ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_calloc.c ft_strdup.c ft_atoi.c\
					ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_utoa.c\
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
					ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
LIBFT_SRC			:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRC_LIST))
LIBFT_OBJ_LST		:= $(patsubst %.c, %.o, $(LIBFT_SRC_LIST))
LIBFT_OBJ			:= $(addprefix $(OBJDIR)/, $(LIBFT_OBJ_LST))

GNL_DIR				:= gnl
GNL_SRC_LIST		:= get_next_line.c\
					get_next_line_utils.c
GNL_SRC				:= $(addprefix $(GNL_DIR)/, $(GNL_SRC_LIST))
GNL_OBJ_LST			:= $(patsubst %.c, %.o, $(GNL_SRC_LIST))
GNL_OBJ				:= $(addprefix $(OBJDIR)/, $(GNL_OBJ_LST))

FT_PRINTF_DIR		:= ft_printf
FT_PRINTF_SRC_LIST	:= ft_printf.c ft_printf_utils.c ft_printf_convert.c\
					   ft_convert_integer.c ft_convert_pointer.c ft_convert_base.c\
					   ft_convert_char_and_str.c specs_setup.c width.c precision.c

FT_PRINTF_SRC		:= $(addprefix $(FT_PRINTF_DIR)/, $(FT_PRINTF_SRC_LIST))
FT_PRINTF_OBJ_LST 	:= $(patsubst %.c, %.o, $(FT_PRINTF_SRC_LIST))
FT_PRINTF_OBJ		:= $(addprefix $(OBJDIR)/, $(FT_PRINTF_OBJ_LST))

CFLAGS				:= -O3 -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(LIBFT_OBJ) $(GNL_OBJ) $(FT_PRINTF_OBJ)
	ar rcs $(NAME) $(LIBFT_OBJ) $(GNL_OBJ) $(FT_PRINTF_OBJ)

$(OBJDIR)/%.o: $(LIBFT_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $< 

$(OBJDIR)/%.o: $(GNL_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -DBUFFER_SIZE=42 -I$(INCLUDES) -o $@ $< 

$(OBJDIR)/%.o: $(FT_PRINTF_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $< 

$(OBJDIR):
	mkdir obj

clean: 
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) 

re: fclean all
