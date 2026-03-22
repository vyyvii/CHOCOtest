/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

char *get_value_env(char *needle, char **haystack)
{
    char *new_needle = my_strjoin(needle, "=");
    int len_needle = my_strlen(new_needle);
    int len_haystack = 0;
    char *result = NULL;

    for (int i = 0; haystack[i]; i++) {
        len_haystack = my_strlen(haystack[i]);
        if (my_strncmp(new_needle, haystack[i], len_needle) == 0) {
            result = strslice(haystack[i], len_needle, len_haystack);
            result = (!result) ? my_strdup("") : result;
        }
    }
    free(new_needle);
    return (result) ? result : NULL;
}

static int change_value(char *needle, char ***env, char *change, int i)
{
    char *new_needle = my_strjoin(needle, "=");
    int len = (new_needle) ? my_strlen(new_needle) : 0;
    char *new_value = NULL;

    if (!new_needle)
        return FAILURE;
    if (my_strncmp((*env)[i], new_needle, len) == 0) {
        new_value = my_strjoin_three(needle, "=", change);
        if (!new_value)
            return FAILURE;
        free((*env)[i]);
        (*env)[i] = new_value;
        free(new_needle);
        return SUCCESS;
    }
    free(new_needle);
    return FAILURE;
}

static char **construct_new_setenv(char *needle, char ***env, char *change)
{
    int ac = nb_args(*env);
    char **new_env = malloc(sizeof(char *) * (ac + 2));

    if (!new_env)
        return NULL;
    for (int i = 0; i < ac; i++) {
        new_env[i] = my_strdup((*env)[i]);
        if (!new_env[i]) {
            free_partial_table((void **)new_env, i);
            return NULL;
        }
    }
    new_env[ac] = my_strjoin_three(needle, "=", change);
    if (!new_env[ac]) {
        free_partial_table((void **)new_env, ac);
        return NULL;
    }
    new_env[ac + 1] = NULL;
    return new_env;
}

static int add_value(char *needle, char ***env, char *change)
{
    char **old_env = *env;
    char **new_env = construct_new_setenv(needle, env, change);

    if (!new_env)
        return FAILURE;
    free_table((void **)old_env);
    *env = new_env;
    return SUCCESS;
}

int change_value_env(char *needle, char ***env, char *change)
{
    int i = 0;

    if (!change)
        change = "";
    while ((*env)[i]) {
        if (change_value(needle, env, change, i) == SUCCESS)
            return SUCCESS;
        i++;
    }
    return add_value(needle, env, change);
}

static int exist(char ***env, char *new_needle, int len)
{
    int ac = nb_args(*env);

    for (int i = 0; i < ac; i++) {
        if (my_strncmp((*env)[i], new_needle, len) == 0)
            return 1;
    }
    return 0;
}

static char **construct_new_unsetenv(char ***env, char *new_needle, int len)
{
    int ac = nb_args(*env);
    char **new_env = malloc(sizeof(char *) * ac);
    int j = 0;

    if (!new_env)
        return NULL;
    for (int i = 0; i < ac; i++) {
        if (my_strncmp((*env)[i], new_needle, len) == 0)
            continue;
        new_env[j] = my_strdup((*env)[i]);
        if (!new_env[j]) {
            free_partial_table((void **)new_env, j);
            return NULL;
        }
        j++;
    }
    new_env[ac - 1] = NULL;
    return new_env;
}

int unset_value_env(char *needle, char ***env)
{
    char *new_needle = my_strjoin(needle, "=");
    int len = (new_needle) ? my_strlen(new_needle) : 0;
    char **new_env;
    char **old_env = *env;

    if (!new_needle)
        return FAILURE;
    if (!exist(env, new_needle, len)) {
        free(new_needle);
        return SUCCESS;
    }
    new_env = construct_new_unsetenv(env, new_needle, len);
    if (!new_env) {
        free(new_needle);
        return FAILURE;
    }
    free_table((void **)old_env);
    *env = new_env;
    free(new_needle);
    return SUCCESS;
}
