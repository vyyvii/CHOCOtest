/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

void save_heredoc(params_t *params, int curr)
{
    char *delim = params->execs.rdr[curr].irdr;
    char *input = NULL;

    pipe(params->execs.rdr[curr].heredoc_fd);
    my_putstr("? ");
    input = take_user_input();
    while (input && my_strcmp(input, delim) != 0 && delim) {
        write(params->execs.rdr[curr].heredoc_fd[1], input, my_strlen(input));
        write(params->execs.rdr[curr].heredoc_fd[1], "\n", 1);
        free(input);
        my_putstr("? ");
        input = take_user_input();
    }
    close(params->execs.rdr[curr].heredoc_fd[1]);
    free(input);
    return;
}

static char *clean_file(char *file)
{
    int s = 0;
    int end = 0;
    char *tmp;

    while (file[s] == ' ' || file[s] == '\t')
        s++;
    end = s;
    while (file[end] && file[end] != ' ' && file[end] != '\t'
        && file[end] != '<' && file[end] != '>')
        end++;
    tmp = strslice(file, s, end);
    free(file);
    return tmp;
}

static char *get_file(char *cmd, int *i)
{
    int start = 0;
    int end = 0;
    char *file;

    (*i)++;
    while (cmd[*i] == ' ' || cmd[*i] == '\t')
        (*i)++;
    start = *i;
    while (cmd[*i] && cmd[*i] != ' ' && cmd[*i] != '\t'
        && cmd[*i] != '<' && cmd[*i] != '>')
        (*i)++;
    end = *i;
    file = strslice(cmd, start, end);
    return (file) ? file : NULL;
}

static void detect_add(redirection_t *rdr, char *cmd, int *i)
{
    if (cmd[*i] == '>' && cmd[*i + 1] == '>') {
        rdr->addo = 1;
        (*i)++;
    }
    if (cmd[*i] == '<' && cmd[*i + 1] == '<') {
        rdr->addi = 1;
        (*i)++;
    }
}

static int create_redirection(params_t *params, char **commands, int curr,
    int *i)
{
    redirection_t *rdr = &params->execs.rdr[curr];
    char *cmd = commands[curr];
    char op = cmd[*i];
    char *file;

    rdr->is = 1;
    rdr->effect_pid = curr;
    detect_add(rdr, cmd, i);
    file = get_file(cmd, i);
    if (!file) {
        my_putstr("Missing name for redirect.\n");
        return FAILURE;
    }
    file = clean_file(file);
    if (op == '>')
        rdr->ordr = file;
    else
        rdr->irdr = file;
    (*i)--;
    return SUCCESS;
}

int redirection_operators(params_t *params, char **commands, int curr)
{
    char *extract_cmd = NULL;

    for (int i = 0; commands[curr][i]; i++) {
        if ((commands[curr][i] == '>' || commands[curr][i] == '<')
            && !extract_cmd)
            extract_cmd = strslice(commands[curr], 0, i);
    }
    for (int i = 0; commands[curr][i]; i++) {
        if ((commands[curr][i] == '>' || commands[curr][i] == '<')
            && create_redirection(params, commands, curr, &i) == FAILURE) {
            free(extract_cmd);
            return FAILURE;
        }
    }
    if (!extract_cmd)
        return FAILURE;
    free(commands[curr]);
    commands[curr] = extract_cmd;
    return SUCCESS;
}
