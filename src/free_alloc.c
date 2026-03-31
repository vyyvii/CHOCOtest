/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

char **copy_env(char **envp)
{
    int ac = nb_args(envp);
    char **env = malloc(sizeof(char *) * (ac + 1));

    if (!env || !envp)
        return NULL;
    for (int i = 0; envp[i]; i++) {
        env[i] = my_strdup(envp[i]);
        if (!env[i])
            free_partial_table((void **)env, i);
    }
    env[ac] = NULL;
    int a = 0;
    return env;
}

void free_pipeline(params_t *params)
{
    if (!params)
        return;
    if (params->execs.pids)
        free(params->execs.pids);
    if (params->execs.pipes)
        free(params->execs.pipes);
    if (params->execs.rdr) {
        for (int i = 0; i < params->execs.nb_pid; i++) {
            free(params->execs.rdr[i].ordr);
            free(params->execs.rdr[i].irdr);
        }
        free(params->execs.rdr);
    }
}

void reset_pipeline(pipeline_ctx_t *pipeline)
{
    pipeline->curr_pid = 0;
    pipeline->nb_pid = 0;
    pipeline->nb_pipes = 0;
    pipeline->pids = NULL;
    pipeline->pipes = NULL;
    pipeline->rdr = NULL;
}

params_t set_param(void)
{
    params_t params;
    shell_t sh;
    pipeline_ctx_t pipeline;

    sh.loop = 1;
    sh.envp = NULL;
    sh.last_path = NULL;
    params.sh = sh;
    reset_pipeline(&pipeline);
    params.execs = pipeline;
    return params;
}

int set_program(params_t *params, char **envp)
{
    char *nlspath = get_value_env("NLSPATH", envp);

    params->sh.envp = copy_env(envp);
    if (!params->sh.envp)
        return FAILURE;
    if (!nlspath && change_value_env("NLSPATH", &params->sh.envp,
            "/usr/share/locale/%L/LC_MESSAGES/%N.cat:"
            "/usr/share/locale/%l/LC_MESSAGES/%N.cat") == FAILURE) {
        free_table((void **)params->sh.envp);
        return FAILURE;
    }
    free(nlspath);
    signal(SIGINT, SIG_IGN);
    params->sh.last_path = get_value_env("PATH", envp);
    return SUCCESS;
}
