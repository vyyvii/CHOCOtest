/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

static int detect_error(char *command, int *i, int *has_input, int *has_output)
{
    int error = 0;

    if (command[*i] == '<') {
        if (*has_input)
            error = 1;
        *has_input = 1;
        *i = (command[*i + 1]) ? *i + 1 : *i;
    }
    if (command[*i] == '>') {
        if (*has_output)
            error = 1;
        *has_output = 1;
        *i = (command[*i + 1]) ? *i + 1 : *i;
    }
    return (error) ? FAILURE : SUCCESS;
}

static int is_ambiguous(params_t *params, char *command, int curr)
{
    int has_input = 0;
    int has_output = 0;
    int error = 0;

    if (curr < params->execs.nb_pid - 1 && contains_char(command, '>'))
        error = 1;
    for (int i = 0; command[i] && !error; i++) {
        if (detect_error(command, &i, &has_input, &has_output) == FAILURE)
            error = 1;
    }
    if (error)
        my_putstr_error("Ambiguous output redirect\n");
    return (error) ? 1 : 0;
}

static int invalid_redirection(char *command)
{
    int i = 0;
    int no_before = 1;
    int no_after = 1;

    while (command[i] && command[i] != '>' && command[i] != '<') {
        if (command[i] != ' ' && command[i] != '\t')
            no_before = 0;
        i++;
    }
    while (command[i] == '>' || command[i] == '<')
        i++;
    while (command[i]) {
        if (command[i] != ' ' && command[i] != '\t')
            no_after = 0;
        i++;
    }
    if (no_before || no_after)
        my_putstr_error((no_after) ? "Missing name for redirect.\n"
            : "Invalid null command.\n");
    return (no_before || no_after) ? 1 : 0;
}

static int parse_commands(params_t *params, char **commands)
{
    for (int i = 0; commands[i]; i++) {
        if (params->execs.pipes && my_str_is_only_space(commands[i])) {
            my_putstr_error("Invalid null command.\n");
            return FAILURE;
        }
        if ((contains_char(commands[i], '>') || contains_char(commands[i], '<'))
            && (invalid_redirection(commands[i])
                || is_ambiguous(params, commands[i], i)
                || redirection_operators(params, commands, i) == FAILURE))
            return FAILURE;
        if (params->execs.rdr[i].is
            && params->execs.rdr[i].irdr && params->execs.rdr[i].addi)
            save_heredoc(params, params->execs.nb_pid - 1);
    }
    return SUCCESS;
}

static void set_rdr(params_t *params)
{
    for (int i = 0; i < params->execs.nb_pid; i++) {
        params->execs.rdr[i].is = 0;
        params->execs.rdr[i].addo = 0;
        params->execs.rdr[i].addi = 0;
        params->execs.rdr[i].effect_pid = -1;
        params->execs.rdr[i].irdr = NULL;
        params->execs.rdr[i].ordr = NULL;
        params->execs.rdr[i].heredoc_fd[0] = -1;
        params->execs.rdr[i].heredoc_fd[1] = -1;
    }
}

static int alloc_pipes_redir(params_t *params, char *input, char **commands)
{
    if (contains_char(input, '|')) {
        params->execs.nb_pipes = count_char(input, '|');
        params->execs.pipes = malloc(sizeof(int[2]) * params->execs.nb_pipes);
        if (!params->execs.pipes) {
            free_table((void **)commands);
            return FAILURE;
        }
    }
    params->execs.rdr = malloc(sizeof(redirection_t) * params->execs.nb_pid);
    if (!params->execs.rdr) {
        free_table((void **)commands);
        return FAILURE;
    }
    set_rdr(params);
    return SUCCESS;
}

static char **alloc_all(params_t *params, char *input)
{
    char **commands = str_to_matrice(input, "|");

    if (!commands)
        return NULL;
    params->execs.nb_pid = nb_args(commands);
    params->execs.pids = malloc(sizeof(pid_t) * params->execs.nb_pid);
    if (!params->execs.pids
        || alloc_pipes_redir(params, input, commands) == FAILURE) {
        free_table((void **)commands);
        return NULL;
    }
    return commands;
}

char **operators(params_t *params, char *input)
{
    char **commands = alloc_all(params, input);

    if (!commands)
        return NULL;
    if (params->execs.nb_pid - 1 != params->execs.nb_pipes) {
        my_putstr_error("Invalid null command.\n");
        free_table((void **)commands);
        return NULL;
    }
    if (parse_commands(params, commands) == FAILURE) {
        free_table((void **)commands);
        return NULL;
    }
    return commands;
}
