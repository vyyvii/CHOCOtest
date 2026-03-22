/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

static int find_pid_rdr(params_t *params)
{
    int pid = -1;

    for (int i = 0; i < params->execs.nb_pid; i++) {
        if (params->execs.rdr[i].is
            && params->execs.rdr[i].effect_pid == params->execs.curr_pid) {
            pid = i;
            break;
        }
    }
    return pid;
}

static int get_irdr(params_t *params, int pid, int **fd)
{
    if (params->execs.rdr[pid].irdr) {
        if (!params->execs.rdr[pid].addi)
            (*fd)[0] = open(params->execs.rdr[pid].irdr, O_RDONLY);
        if (params->execs.rdr[pid].addi)
            (*fd)[0] = params->execs.rdr[pid].heredoc_fd[0];
        if ((*fd)[0] == -1)
            return FAILURE;
    }
    return SUCCESS;
}

static int *get_fd(params_t *params, int pid)
{
    int *fd = malloc(sizeof(int) * 2);

    fd[0] = -1;
    fd[1] = -1;
    if (params->execs.rdr[pid].ordr) {
        if (!params->execs.rdr[pid].addo)
            fd[1] = open(params->execs.rdr[pid].ordr,
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (params->execs.rdr[pid].addo)
            fd[1] = open(params->execs.rdr[pid].ordr,
                O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd[1] == -1)
            return NULL;
    }
    return (get_irdr(params, pid, &fd) == FAILURE) ? NULL : fd;
}

static void duplicate_fd(params_t *params, int *fd, int pid)
{
    if (params->execs.rdr[pid].ordr)
        dup2(fd[1], STDOUT_FILENO);
    if (params->execs.rdr[pid].irdr)
        dup2(fd[0], STDIN_FILENO);
}

static int redirection_handling(params_t *params)
{
    int *fd = NULL;
    int pid = find_pid_rdr(params);

    if (pid == -1)
        return SUCCESS;
    fd = get_fd(params, pid);
    if (!fd) {
        if (params->execs.rdr[pid].irdr)
            errno_messages(params->execs.rdr[pid].irdr, 1);
        else
            errno_messages(params->execs.rdr[pid].ordr, 1);
        return FAILURE;
    }
    duplicate_fd(params, fd, pid);
    if (fd[0] != -1)
        close(fd[0]);
    if (fd[1] != -1)
        close(fd[1]);
    free(fd);
    return SUCCESS;
}

static void pipe_handling(params_t *params)
{
    if (params->execs.curr_pid > 0) {
        dup2(params->execs.pipes[params->execs.curr_pid - 1][0], STDIN_FILENO);
        close(params->execs.pipes[params->execs.curr_pid - 1][0]);
        close(params->execs.pipes[params->execs.curr_pid - 1][1]);
    }
    if (params->execs.curr_pid < params->execs.nb_pid - 1) {
        dup2(params->execs.pipes[params->execs.curr_pid][1], STDOUT_FILENO);
        close(params->execs.pipes[params->execs.curr_pid][0]);
        close(params->execs.pipes[params->execs.curr_pid][1]);
    }
}

void child_process(params_t *params, char **command, char *comm,
    function_pipe_t *func)
{
    if (params->execs.pipes)
        pipe_handling(params);
    if (redirection_handling(params) == FAILURE)
        exit(0);
    if (func)
        func->function(params, func->array);
    if (comm) {
        execve(comm, command, params->sh.envp);
        errno_messages(comm, 0);
    }
    exit(0);
}
