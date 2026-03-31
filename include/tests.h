/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#ifndef TEST_H
    #define TEST_H
    #include <criterion/criterion.h>
    #include <criterion/redirect.h>
    #include "my.h"

// TOOL
void redirect_all_std(void);
char **make_env(void);
params_t make_params(void);
params_t make_params_parse(char *input);

#endif /* TEST_H */
