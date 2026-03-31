/*
** EPITECH PROJECT, 2026
** HEADER UtilsLib
** File description:
** Header file for UtilsLib
*/

/**
 * @file utilslib.h
 * @brief This file is the header file of UtilsLib.
 *
 * @details
 * This library provides utilities for:
 * - character classification (letter, digit, case),
 * - integer manipulation (arithmetic, primality, sorting),
 * - conversion between strings and numbers,
 * - string operations (tests, copies, joins, search),
 * - management of string arrays (matrices),
 * - low-level memory primitives (copy, swap, file reading).
 *
 * Functions that allocate memory return a pointer that must be freed
 * by the caller via `free`. Some functions use system calls and standard
 * library functions that may be forbidden depending on the rules
 * (e.g., open/read/close, getline/strcspn). See @warning in each description.
 *
 * @note Time complexity is indicated when relevant.
 * @author Victor Defauchy
 * @date 15.03.2026
 */

#ifndef UTILSLIB
    #define UTILSLIB
    #define SUCCESS 0
    #define FAILURE 84
    #define CHUNK 128
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <string.h>
    #include <limits.h>
    #include <math.h>
    #include <sys/types.h>
    #include <sys/stat.h>

/**
 * @defgroup char Characters
 * @brief Utility functions related to character classification.
 */
/**
 * @defgroup maths Mathematics
 * @brief Utility functions related to mathematics.
 */
/**
 * @defgroup int_str Strings ↔ Numbers
 * @brief Conversions and printing of numbers in text form and vice versa.
 */
/**
 * @defgroup str Strings
 * @brief Operations on C strings (null-terminated).
 */
/**
 * @defgroup matrice String matrices
 * @brief Tools for arrays of strings (char**).
 */
/**
 * @defgroup mem Memory and I/O
 * @brief Low-level memory tools and file reading.
 */

/* ============================================================
** CHAR
** ============================================================ */

int is_digit(char c);
int is_letter(char c);
int is_lowerletter(char c);
int is_upperletter(char c);
void my_putchar(char c);
void my_putchar_error(char c);
int nb_chars(char *str, char c);

/* ============================================================
** MATHS
** ============================================================ */

typedef struct abcsizeij_s {
    double **A;
    double **B;
    double **C;
    int i;
    int j;
    int sizeB;
} abcsizeij_t;

double my_power(int nb, int p);
int my_find_prime_sup(int nb);
int my_is_prime(int nb);
int my_isneg(int n);
void my_sort_int_array(int *array, int size);
double my_sqrt(double nb);
double **multiplies_two_matrices(double **A, double **B, int sizeA, int sizeB);
double **add_two_matrices(double **A, double **B, int sizeA, int sizeB);
double **divise_matrice_by_double(double **A, int sizeA, double divise_by);
double **construct_matrice(double *A, int sizeA);
double **identity_matrice(int len);
int my_factorial(int nb);

/* ============================================================
** INT_STR
** ============================================================ */

int my_getnbr(char const *str);
double my_get_double_nbr(char const *str);
long long my_get_longlong_nbr(char const *str);
int my_put_nbr(int nb);
int my_put_nbr_err(int nb);
int verif_int(char *number, int *result);
int verif_double(char *number, double *result);
int get_precision(char *number);

/* ============================================================
** STR
** ============================================================ */

int contains_char(char *str, char c);
int count_char(char *str, char c);

void my_putstr(char const *str);
void my_putstr_error(char const *str);
int my_strlen(char const *str);

char *my_revstr(char *str);
char *my_strcapitalize(char *str);
char *my_strlowcase(char *str);
char *my_strupcase(char *str);

int my_str_is_only_space(char *str);
int my_str_isalpha(char const *str);
int my_str_isalphanumeric(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isnum(char const *str);
int my_str_isprintable(char const *str);

int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
int my_strcmp_no_case(char *a, char *b);

char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, size_t size);
char *my_strdup(char const *str);

char *my_strjoin(char const *s1, char const *s2);
char *my_strjoin_three(char const *s1, char const *s2, char const *s3);

char *my_strstr(char *str, char const *to_find);
char *strslice(char *str, int from, int to);

void putcat(char *txt1, char *txt2);
char *take_user_input(void);
char **str_to_array(char *str);

/* ============================================================
** matrice
** ============================================================ */

char **uniq_words(char *str);
void alpha_sort(char **array, int is_reverse);

char **str_to_matrice(char *str, char *delims);
char **str_to_word_array(char *str);
char **str_to_word_array_space(char *str);

int nb_args(char **args);
int my_show_word_array(char const **tab);
int count_lines(char *str);

/* ============================================================
** MEM
** ============================================================ */

void my_swap(void *a, void *b, size_t size);
void *my_memcpy(void *dest, const void *src, size_t n);

char *open_file(char *file);

void free_table(void **table);
void free_partial_table(void **table, int n);

#endif /* !UTILSLIB */
