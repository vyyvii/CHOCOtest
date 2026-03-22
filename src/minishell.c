/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

static void create_fail_file(params_t *params)
{
    int fd = -1;

    for (int i = 0; i < params->execs.nb_pid; i++) {
        if (params->execs.rdr[i].is &&
            params->execs.curr_pid == params->execs.rdr[i].effect_pid) {
            open(params->execs.rdr[i].ordr, O_CREAT | O_TRUNC, 0644);
            close(fd);
        }
    }
}

static int launch_commands(params_t *params, char **inputs)
{
    int ret = SUCCESS;
    int f_ret = ret;

    for (int i = 0; inputs[i]; i++) {
        ret = command_handler(params, inputs[i], i);
        f_ret = (ret == FAILURE) ? FAILURE : f_ret;
    }
    if (ret == FAILURE && params->execs.rdr)
        create_fail_file(params);
    if (params->execs.pipes) {
        for (int i = 0; i < params->execs.nb_pid; i++) {
            ret = parents_process(params->execs.pids[i]);
            f_ret = (ret == FAILURE) ? FAILURE : f_ret;
        }
    }
    free_table((void **)inputs);
    free_pipeline(params);
    return f_ret;
}

static int launch_pipelines(params_t *params, int *ret)
{
    char **inputs = NULL;
    char *input = take_user_input();
    char **pipelines = (input) ? str_to_matrice(input, ";") : NULL;

    if (!pipelines)
        return FAILURE;
    for (int i = 0; pipelines[i] && !my_str_is_only_space(input); i++) {
        reset_pipeline(&params->execs);
        inputs = operators(params, pipelines[i]);
        if (!inputs) {
            free(params->execs.rdr);
            params->execs.rdr = NULL;
            free_pipeline(params);
            break;
        }
        *ret = launch_commands(params, inputs);
    }
    free(input);
    free_table((void **)pipelines);
    return SUCCESS;
}

int minishell(int ac, char **envp)
{
    params_t params = set_param();
    int ret = SUCCESS;

    if (ac != 1 || set_program(&params, envp) == FAILURE)
        return FAILURE;
    while (params.sh.loop == 1) {
        if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
            my_putstr("$> ");
        if (launch_pipelines(&params, &ret) == FAILURE)
            break;
    }
    free_table((void **)params.sh.envp);
    free(params.sh.last_path);
    return ret;
}
