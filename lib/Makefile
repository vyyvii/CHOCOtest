##
## EPITECH PROJECT, 2026
## Makefile UtilsLib
## File description:
## Makefile UtilsLib
##

.PHONY: all clean fclean re

SRC = 	src/char/is_digit.c \
		src/char/is_letter.c \
		src/char/is_lowerletter.c \
		src/char/is_upperletter.c \
		src/char/my_putchar.c \
		src/char/nb_char.c \
		src/maths/my_find_prime_sup.c \
		src/maths/my_is_prime.c \
		src/maths/my_isneg.c \
		src/maths/my_power.c \
		src/maths/my_sort_int_array.c \
		src/maths/my_factorial.c \
		src/maths/matrice.c \
		src/maths/square_root.c \
		src/int_str/get_precision.c \
		src/int_str/my_get_double_nbr.c \
		src/int_str/my_get_longlong_nbr.c \
		src/int_str/my_getnbr.c \
		src/int_str/my_put_nbr.c \
		src/int_str/verif_double.c \
		src/int_str/verif_int.c \
		src/matrice/ac.c \
		src/matrice/alpha_sort.c \
		src/matrice/count_lines.c \
		src/matrice/my_show_word_array.c \
		src/matrice/str_to_array.c \
		src/matrice/str_to_matrice.c \
		src/mem/free_table.c \
		src/mem/my_memcpy.c \
		src/mem/my_strcpy.c \
		src/mem/my_strdup.c \
		src/mem/my_strncpy.c \
		src/mem/my_swap.c \
		src/mem/open_file.c \
		src/mem/strslice.c \
		src/mem/my_strjoin_three.c \
		src/mem/my_strjoin.c \
		src/mem/putcat.c \
		src/str/count_contains_char.c \
		src/str/my_putstr.c \
		src/str/my_revstr.c \
		src/str/my_str_is_only_space.c \
		src/str/my_str_isalpha.c \
		src/str/my_str_isalphanumeric.c \
		src/str/my_str_islower.c \
		src/str/my_str_isnum.c \
		src/str/my_str_isprintable.c \
		src/str/my_str_isupper.c \
		src/str/my_strcapitalize.c \
		src/str/my_strcmp_no_case.c \
		src/str/my_strcmp.c \
		src/str/my_strlen.c \
		src/str/my_strncmp.c \
		src/str/my_strstr.c \
		src/str/my_strupcase.c \
		src/str/my_strlowcase.c \
		src/str/take_user_input.c
OBJ := 	$(patsubst %.c,%.o,$(SRC))

CC = epiclang
CFLAGS = -Wall -Wextra -g3 -Iinclude -O0

NAME = libUtilsLib.a
REMOVE = rm -f -r

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME) a.out
	$(REMOVE) **.gcno **.gcda **.html **.css

re: fclean all
