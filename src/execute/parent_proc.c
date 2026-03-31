/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

static char *get_result(char *comm, char **path_array)
{
    char *test_path = NULL;
    char *result = NULL;

    if (!path_array)
        return result;
    for (int i = 0; path_array[i]; i++){
        test_path = my_strjoin_three(path_array[i], "/", comm);
        if (!test_path)
            break;
        if (access(test_path, F_OK) == 0) {
            result = test_path;
            break;
        }
        free(test_path);
        test_path = NULL;
    }
    return result;
}

static char *comm_from_path(char *comm, char **env, params_t *params)
{
    char *path = get_value_env("PATH", env);
    char **path_array = NULL;
    char *result = NULL;

    if (!path)
        path = my_strdup(params->sh.last_path);
    path_array = str_to_matrice(path, ":");
    result = get_result(comm, path_array);
    free(path);
    if (path_array)
        free_table((void **)path_array);
    if (!result)
        return NULL;
    return result;
}

static char *get_comm(params_t *params, char **command)
{
    char *comm = NULL;

    if (contains_char(command[0], '/')) {
        comm = my_strdup(command[0]);
        if (!comm)
            return NULL;
        if (access(comm, F_OK) == 0)
            return comm;
        free(comm);
        return NULL;
    }
    return comm_from_path(command[0], params->sh.envp, params);
}

int parents_process(pid_t pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGSEGV)
            my_putstr_error("Segmentation fault");
        if (WTERMSIG(status) == SIGFPE)
            my_putstr_error("Floating exception");
        if (__WCOREDUMP(status))
            my_putstr_error(" (core dumped)");
        my_putchar_error('\n');
        return 128 + WTERMSIG(status);
    }
    return (WIFEXITED(status)) ? WEXITSTATUS(status) : 0;
}

static int fork_and_launch(params_t *params, char **command, char *comm,
    function_pipe_t *func)
{
    int ret = SUCCESS;

    params->execs.pids[params->execs.curr_pid] = fork();
    if (params->execs.pids[params->execs.curr_pid] == -1) {
        free(comm);
        return FAILURE;
    }
    if (params->execs.pids[params->execs.curr_pid] == 0)
        child_process(params, command, comm, func);
    if (!params->execs.pipes && params->execs.pids[params->execs.curr_pid] > 0)
        ret = parents_process(params->execs.pids[params->execs.curr_pid]);
    return ret;
}

int use_execve(params_t *params, char **command, function_pipe_t *func)
{
    char *comm;
    int ret = SUCCESS;

    comm = get_comm(params, command);
    if (!comm)
        return FAILURE;
    if (params->execs.pipes
        && params->execs.curr_pid < params->execs.nb_pid - 1)
        pipe(params->execs.pipes[params->execs.curr_pid]);
    ret = fork_and_launch(params, command, comm, func);
    if (params->execs.pipes && params->execs.curr_pid > 0) {
        close(params->execs.pipes[params->execs.curr_pid - 1][0]);
        close(params->execs.pipes[params->execs.curr_pid - 1][1]);
    }
    params->execs.curr_pid++;
    free(comm);
    return ret;
}
