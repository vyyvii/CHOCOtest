/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

static char *get_path(params_t *params, char **command)
{
    if (!command[1] || my_strcmp(command[1], "~") == 0)
        return get_value_env("HOME", params->sh.envp);
    if (my_strcmp(command[1], "-") == 0)
        return get_value_env("OLDPWD", params->sh.envp);
    return my_strdup(command[1]);
}

static int change_directory(params_t *params, char *path, char *pwd)
{
    int dir = 0;
    char *current_dir = NULL;
    int ret = SUCCESS;

    if (!path)
        return FAILURE;
    dir = (path) ? chdir(path) : -1;
    if (dir != 0) {
        errno_messages(path, 1);
        return FAILURE;
    }
    current_dir = getcwd(NULL, 0);
    if (!current_dir)
        return FAILURE;
    if (change_value_env("OLDPWD", &params->sh.envp, pwd) == FAILURE ||
        change_value_env("PWD", &params->sh.envp, current_dir) == FAILURE)
        ret = FAILURE;
    free(current_dir);
    return ret;
}

int c_cd(params_t *params, char **command)
{
    int ac = nb_args(command);
    char *path = get_path(params, command);
    char *pwd = get_value_env("PWD", params->sh.envp);
    int ret = SUCCESS;

    (void)params;
    if (ac > 2) {
        my_putstr_error("cd: Too many arguments.\n");
        free(path);
        free(pwd);
        return FAILURE;
    }
    ret = change_directory(params, path, pwd);
    free(path);
    free(pwd);
    return ret;
}

int c_env(params_t *params, char **command)
{
    int ac = nb_args(command);

    if (ac == 1) {
        for (int i = 0; params->sh.envp[i]; i++) {
            my_putstr(params->sh.envp[i]);
            my_putchar('\n');
        }
        return SUCCESS;
    }
    return FAILURE;
}

static int change_last_path(params_t *params)
{
    char *last_path = get_value_env("PATH", params->sh.envp);
    char *dup = NULL;

    if (!last_path)
        return FAILURE;
    dup = my_strdup(last_path);
    free(last_path);
    if (!dup)
        return FAILURE;
    if (params->sh.last_path)
        free(params->sh.last_path);
    params->sh.last_path = dup;
    return SUCCESS;
}

int c_setenv(params_t *params, char **command)
{
    int ac = nb_args(command);

    if (ac == 1)
        return c_env(params, command);
    if (ac > 3) {
        my_putstr_error("setenv: Too many arguments.\n");
        return FAILURE;
    }
    if (!my_str_isalphanumeric(command[1])) {
        my_putstr_error("setenv: Variable name must contain");
        my_putstr_error(" alphanumeric characters.\n");
        return FAILURE;
    }
    if (!is_letter(command[1][0])) {
        my_putstr_error("setenv: Variable name must begin with a letter.\n");
        return FAILURE;
    }
    if (change_value_env(command[1], &params->sh.envp, command[2]) == FAILURE)
        return FAILURE;
    return change_last_path(params);
}

int c_unsetenv(params_t *params, char **command)
{
    int ac = nb_args(command);

    if (ac == 1) {
        my_putstr_error("unsetenv: Too few arguments.\n");
        return FAILURE;
    }
    for (int i = 1; command[i]; i++) {
        if (unset_value_env(command[i], &params->sh.envp) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int c_exit(params_t *params, char **command)
{
    int ac = nb_args(command);

    if (ac != 1) {
        my_putstr_error("exit: Expression Syntax.\n");
        return FAILURE;
    }
    params->sh.loop = 0;
    my_putstr("exit\n");
    return SUCCESS;
}
