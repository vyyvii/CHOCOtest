/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

void test_copy_env(void **state)
{
    char **envp = make_env();
    char **env = copy_env(envp);

    (void)state;
    assert_non_null(env);
    assert_string_equal(env[0], "USER=victor");
    assert_string_equal(env[1], "PATH=/bin:/usr/bin");
    assert_string_equal(env[2], "HOME=/home/victordfc");
    assert_null(env[3]);

    free_table((void **)env);
    free_table((void **)envp);
}

void test_get_value_env(void **state)
{
    char **env = make_env();
    char *value = get_value_env("PATH", env);

    (void)state;
    assert_string_equal(value, "/bin:/usr/bin");
    free(value);

    value = get_value_env("HOME", env);
    assert_string_equal(value, "/home/victordfc");
    free(value);

    value = get_value_env("test", env);
    assert_null(value);

    free_table((void **)env);
}

void test_change_value_env(void **state)
{
    char **env = make_env();

    (void)state;
    assert_int_equal(change_value_env("USER", &env, "bob"), SUCCESS);
    assert_string_equal(env[0], "USER=bob");

    assert_int_equal(change_value_env("SHELL", &env, "/bin/bash"), SUCCESS);
    assert_string_equal(env[3], "SHELL=/bin/bash");

    assert_int_equal(change_value_env("EMPTY", &env, NULL), SUCCESS);
    assert_string_equal(env[4], "EMPTY=");

    assert_null(env[5]);

    free_table((void **)env);
}

void test_unset_value_env(void **state)
{
    char **env = make_env();

    (void)state;
    assert_int_equal(unset_value_env("PATH", &env), SUCCESS);
    assert_null(get_value_env("PATH", env));
    assert_int_equal(unset_value_env("test", &env), SUCCESS);
    assert_string_equal(get_value_env("USER", env), "victor");

    free_table((void **)env);
}
