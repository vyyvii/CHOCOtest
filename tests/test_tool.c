/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

char **make_env(void)
{
    char **env = malloc(sizeof(char *) * 5);

    env[0] = my_strdup("USER=victor");
    env[1] = my_strdup("PATH=/bin:/usr/bin");
    env[2] = my_strdup("HOME=/home/victordfc");
    env[3] = NULL;
    return env;
}

params_t make_params(void)
{
    params_t params;
    shell_t sh;
    pipeline_ctx_t pipeline;

    sh.loop = 1;
    sh.envp = make_env();
    sh.last_path = my_strdup("/home/victordfc");
    params.sh = sh;
    reset_pipeline(&pipeline);
    params.execs = pipeline;
    params.execs.pids = malloc(sizeof(pid_t));
    params.execs.rdr = malloc(sizeof(redirection_t));
    params.execs.rdr[0].is = 0;
    params.execs.nb_pid = 1;
    params.execs.curr_pid = 0;
    params.execs.pipes = NULL;
    return params;
}

params_t make_params_parse(char *input)
{
    params_t params = make_params();

    params.execs.nb_pid = 1;
    params.execs.nb_pipes = 0;
    params.execs.curr_pid = 0;
    params.execs.pipes = NULL;
    params.execs.rdr = malloc(sizeof(redirection_t));
    params.execs.rdr[0].is = 0;
    params.execs.rdr[0].addo = 0;
    params.execs.rdr[0].addi = 0;
    params.execs.rdr[0].effect_pid = -1;
    params.execs.rdr[0].irdr = NULL;
    params.execs.rdr[0].ordr = NULL;

    return params;
}

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
