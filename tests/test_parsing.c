/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

Test(redirection, simple_output, .init = redirect_all_std)
{
    params_t params = make_params_parse(NULL);
    char **cmds = malloc(sizeof(char *) * 2);
    int ret = SUCCESS;

    cmds[0] = my_strdup("ls > file.txt");
    cmds[1] = NULL;
    ret = redirection_operators(&params, cmds, 0);
    cr_assert_eq(ret, SUCCESS);
    cr_assert_str_eq(cmds[0], "ls ");
    cr_assert_eq(params.execs.rdr[0].is, 1);
    cr_assert_str_eq(params.execs.rdr[0].ordr, "file.txt");
    free_table((void **)cmds);
}

Test(redirection, simple_input, .init = redirect_all_std)
{
    params_t params = make_params_parse(NULL);
    char **cmds = malloc(sizeof(char *) * 2);
    int ret = SUCCESS;

    cmds[0] = my_strdup("cat < input.txt");
    cmds[1] = NULL;
    ret = redirection_operators(&params, cmds, 0);
    cr_assert_eq(ret, SUCCESS);
    cr_assert_str_eq(params.execs.rdr[0].irdr, "input.txt");
    free_table((void **)cmds);
}

Test(redirection, missing_file, .init = redirect_all_std)
{
    params_t params = make_params_parse(NULL);
    char **cmds = malloc(sizeof(char *) * 2);
    int ret = SUCCESS;

    cmds[0] = my_strdup("ls > ");
    cmds[1] = NULL;
    ret = redirection_operators(&params, cmds, 0);
    cr_assert_eq(ret, FAILURE);
    free_table((void **)cmds);
}

Test(redirection, append_output, .init = redirect_all_std)
{
    params_t params = make_params_parse(NULL);
    char **cmds = malloc(sizeof(char *) * 2);
    int ret = SUCCESS;

    cmds[0] = my_strdup("ls >> file.txt");
    cmds[1] = NULL;
    ret = redirection_operators(&params, cmds, 0);
    cr_assert_eq(ret, SUCCESS);
    cr_assert_eq(params.execs.rdr[0].addo, 1);
    free_table((void **)cmds);
}

Test(operators, simple_command, .init = redirect_all_std)
{
    params_t params = make_params();
    char **cmds = operators(&params, "ls");

    cr_assert_not_null(cmds);
    cr_assert_str_eq(cmds[0], "ls");
    cr_assert_null(cmds[1]);
    free_table((void **)cmds);
}

Test(operators, simple_pipe, .init = redirect_all_std)
{
    params_t params = make_params();
    char **cmds = operators(&params, "ls | wc");

    cr_assert_not_null(cmds);
    cr_assert_str_eq(cmds[0], "ls ");
    cr_assert_str_eq(cmds[1], " wc");
    free_table((void **)cmds);
}

Test(operators, invalid_null_command, .init = redirect_all_std)
{
    params_t params = make_params();
    char **cmds = operators(&params, "ls || wc");

    cr_assert_null(cmds);
}

Test(operators, ambiguous_redirect, .init = redirect_all_std)
{
    params_t params = make_params();
    char **cmds = operators(&params, "ls > file | wc");

    cr_assert_null(cmds);
}

Test(operators, only_redirection, .init = redirect_all_std)
{
    params_t params = make_params();
    char **cmds = operators(&params, "> file");

    cr_assert_null(cmds);
}
