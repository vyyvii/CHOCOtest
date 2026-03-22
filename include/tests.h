/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#ifndef TEST_H
    #define TEST_H
    #include <stddef.h>
    #include <stdarg.h>
    #include <setjmp.h>
    #include <cmocka.h>
    #include "my.h"

// MAIN
char *capture_stdout(void (*func)(void));
params_t make_params(void);
char **make_env(void);

// TEST COMMANDES
void test_command_handler(void **state);
void test_execve(void **state);

// TEST ENV
void test_copy_env(void **state);
void test_get_value_env(void **state);
void test_change_value_env(void **state);
void test_unset_value_env(void **state);

#endif /* TEST_H */
