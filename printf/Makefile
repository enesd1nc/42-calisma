NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC = ft_printf.c ft_utils_hex.c ft_utils_int.c\
      ft_utils_p.c ft_utils_str.c 	
OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
		ar rcs $(NAME) $?
#ar rcs den sonra ilk gelen olusturulacak kutuphane ardından gelenlerde içine konulacak nesne dosyaları.$? sadece değiştirilen dosyaları yeniden kütüphaneye eklenmesini sağlar.
%.o : %.c
		$(CC) -c $(CFLAGS) $< -o $@
#<$ kullanıcıdan gelen ilk girdi $@ tüm parametreleri temsil eder

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
