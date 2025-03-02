NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MINILIBX = minilibx-linux/libmlx.a
MLXFLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm
INCLUDES = -I. -I./minilibx-linux -I./get_next_line

SRC = main.c \
	read_map.c \
	check_collectiables.c \
	map_control.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c 

OBJ = $(SRC:.c=.o)

all : $(MINILIBX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MINILIBX):
	@make -C minilibx-linux

clean:
	rm -f $(OBJ)
	@make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	@make -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re