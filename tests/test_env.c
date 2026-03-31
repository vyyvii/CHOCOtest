/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

Test(env, copy_env, .init = redirect_all_std)
{
    char **envp = make_env();
    char **env = copy_env(envp);

    cr_assert_not_null(env);
    cr_assert_str_eq(env[0], "USER=victor");
    cr_assert_str_eq(env[1], "PATH=/bin:/usr/bin");
    cr_assert_str_eq(env[2], "HOME=/home/victordfc");
    cr_assert_null(env[3]);
    free_table((void **)env);
    free_table((void **)envp);
}

Test(env, get_value_env, .init = redirect_all_std)
{
    char **env = make_env();
    char *value;

    value = get_value_env("PATH", env);
    cr_assert_str_eq(value, "/bin:/usr/bin");
    free(value);
    value = get_value_env("HOME", env);
    cr_assert_str_eq(value, "/home/victordfc");
    free(value);
    value = get_value_env("test", env);
    cr_assert_null(value);
    free_table((void **)env);
}

Test(env, change_value_env, .init = redirect_all_std)
{
    char **env = make_env();

    cr_assert_eq(change_value_env("USER", &env, "bob"), SUCCESS);
    cr_assert_str_eq(env[0], "USER=bob");
    cr_assert_eq(change_value_env("SHELL", &env, "/bin/bash"), SUCCESS);
    cr_assert_str_eq(env[3], "SHELL=/bin/bash");
    cr_assert_eq(change_value_env("EMPTY", &env, NULL), SUCCESS);
    cr_assert_str_eq(env[4], "EMPTY=");
    cr_assert_null(env[5]);
    free_table((void **)env);
}

Test(env, unset_value_env, .init = redirect_all_std)
{
    char **env = make_env();

    cr_assert_eq(unset_value_env("PATH", &env), SUCCESS);
    cr_assert_null(get_value_env("PATH", env));
    cr_assert_eq(unset_value_env("test", &env), SUCCESS);
    cr_assert_str_eq(get_value_env("USER", env), "victor");
    free_table((void **)env);
}

Test(env, get_value_env_multiple_entries, .init = redirect_all_std)
{
    char *env[] = {
        "PATH=/bin",
        "PATH=/usr/bin",
        NULL
    };
    char *value = get_value_env("PATH", env);

    cr_assert_str_eq(value, "/usr/bin");
    free(value);
}

Test(env, get_value_env_empty_value, .init = redirect_all_std)
{
    char *env[] = {
        "EMPTY=",
        NULL
    };
    char *value = get_value_env("EMPTY", env);

    cr_assert_str_eq(value, "");
    free(value);
}

Test(env, change_value_existing_vs_new, .init = redirect_all_std)
{
    char **env = make_env();
    char *val = NULL;

    cr_assert_eq(change_value_env("USER", &env, "alice"), SUCCESS);
    cr_assert_str_eq(env[0], "USER=alice");
    cr_assert_eq(change_value_env("NEWVAR", &env, "42"), SUCCESS);
    val = get_value_env("NEWVAR", env);
    cr_assert_str_eq(val, "42");
    free(val);
    free_table((void **)env);
}

Test(env, unset_last_element, .init = redirect_all_std)
{
    char *env[] = {
        strdup("USER=victor"),
        strdup("PATH=/bin"),
        NULL
    };
    char **env_dup = copy_env(env);

    cr_assert_eq(unset_value_env("PATH", &env_dup), SUCCESS);
    cr_assert_null(get_value_env("PATH", env_dup));
    free_table((void **)env_dup);
}

Test(env, unset_all, .init = redirect_all_std)
{
    char *env[] = {
        strdup("ONLY=1"),
        NULL
    };
    char **env_dup = copy_env(env);

    cr_assert_eq(unset_value_env("ONLY", &env_dup), SUCCESS);
    cr_assert_null(env_dup[0]);
    free_table((void **)env_dup);
}

Test(env, change_empty_string, .init = redirect_all_std)
{
    char **env = make_env();
    char *val = NULL;

    cr_assert_eq(change_value_env("USER", &env, ""), SUCCESS);
    val = get_value_env("USER", env);
    cr_assert_str_eq(val, "");
    free(val);
    free_table((void **)env);
}

Test(env, unset_non_existing, .init = redirect_all_std)
{
    char **env = make_env();

    cr_assert_eq(unset_value_env("DOESNOTEXIST", &env), SUCCESS);
    cr_assert_str_eq(get_value_env("USER", env), "victor");
    free_table((void **)env);
}


