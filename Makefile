INC=/usr/include
HT=Linux
DOCP=do_cp

INCLIB=$(INC)/../lib

CC=gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I$(HEADERS) -I$(MINILIBX_HEADER)

HEADERS = includes/
SRC_DIR = srcs/
OBJ_DIR = objs/

MINILIBX_HEADER = mlx_linux/
MINILIBX = ./mlx_linux/libmlx.a

NAME= fdf

SRC = fdf.c close_program.c ft_split.c tools.c tools_2.c tools_3.c color.c draw.c data_map.c parse_map.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
FIL = $(addprefix $(OBJ_DIR),$(OBJ))

all	:$(NAME)

$(NAME)	:$(FIL) $(MINILIBX)
	$(CC) -o $(NAME) $(FIL) -Lmlx_linux -lmlx -lXext -lX11 -lm -lbsd

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(MINILIBX):
	@echo "\033[0;32mCreating $(MINILIBX)"
	@$(MAKE) -sC $(MINILIBX_HEADER)

clean	:
	@echo "\033[0;31mRemovig obj..."
	rm -f $(FIL)
	@$(MAKE) -sC $(MINILIBX_HEADER)	clean

fclean: clean
	@echo "\033[0;31mRemoving objs directoy..."
	rmdir $(OBJ_DIR)
	@echo "\033[0;31mRemovig .sh..."
	rm -f $(NAME)

re	: clean all
