/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

void errno_messages(char *cmd, int from_cd)
{
    my_putstr_error(cmd);
    if (errno == ENOEXEC)
        my_putstr_error(": Exec format error. Binary file not executable.\n");
    if (errno == EACCES)
        my_putstr_error(": Permission denied.\n");
    if (errno == ENOTDIR)
        my_putstr_error(": Not a directory.\n");
    if (errno == EISDIR)
        my_putstr_error(": Is a directory.\n");
    if (errno == ENOENT && from_cd)
        my_putstr_error(": No such file or directory.\n");
}

static int (*get_func(char **array))(params_t *, char **)
{
    static const commands_t commands[] = {
        (commands_t){"cd", c_cd},
        (commands_t){"setenv", c_setenv},
        (commands_t){"unsetenv", c_unsetenv},
        (commands_t){"env", c_env},
        (commands_t){"exit", c_exit},
        (commands_t){NULL, NULL},
    };
    int (*function)(params_t *, char **) = NULL;

    for (int i = 0; commands[i].command; i++) {
        if (my_strcmp(array[0], commands[i].command) == 0)
            function = commands[i].function;
    }
    return function;
}

static int launch_function(int (*function)(params_t *, char **),
    params_t *params, char **array, int i)
{
    function_pipe_t func;

    if (params->execs.pipes || params->execs.rdr[i].is) {
        func.array = array;
        func.function = function;
        return use_execve(params, array, &func);
    }
    return function(params, array);
}

int command_handler(params_t *params, char *request, int i)
{
    int is_only_space = my_str_is_only_space(request);
    char **array = (!is_only_space) ? str_to_array(request) : NULL;
    int (*function)(params_t *, char **) = NULL;
    int ret = SUCCESS;

    if (!array)
        return (is_only_space) ? SUCCESS : FAILURE;
    function = get_func(array);
    if (function)
        ret = launch_function(function, params, array, i);
    else {
        ret = use_execve(params, array, NULL);
        if (ret == FAILURE) {
            my_putstr_error(array[0]);
            my_putstr_error(": Command not found.\n");
        }
    }
    free_table((void **)array);
    return ret;
}
