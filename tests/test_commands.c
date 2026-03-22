/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

Test(command_handler, basic_builtins, .init = redirect_all_std)
{
    params_t params = make_params();

    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "env", 0), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "env too much", 0), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "setenv test test", 0), SUCCESS);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "setenv too much params", 0), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "setenv 4AAA", 0), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "setenv A-A", 0), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "setenv", 0), SUCCESS);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "unsetenv test", 0), SUCCESS);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "unsetenv", 0), FAILURE);
    params.execs.curr_pid = 0;
    change_value_env("HOME", &params.sh.envp, "/tmp");
    cr_assert_eq(command_handler(&params, "cd", 0), SUCCESS);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "cd ~", 0), SUCCESS);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "cd nowhere", 0), FAILURE);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

Test(command_handler, command_not_found, .init = redirect_all_std)
{
    params_t params = make_params();

    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "abc", 0), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "./abc", 0), FAILURE);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

Test(command_handler, exit_behavior, .init = redirect_all_std)
{
    params_t params = make_params();

    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "exit", 0), SUCCESS);
    cr_assert_eq(params.sh.loop, 0);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "exit too much", 0), FAILURE);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

Test(execve, basic_exec, .init = redirect_all_std)
{
    params_t params = make_params();

    char *cmd1[] = {"/bin/true", NULL};
    char *cmd2[] = {"/bin/false", NULL};
    char *cmd3[] = {"true", NULL};
    char *cmd4[] = {"thiscommanddoesnotexist", NULL};
    char *cmd5[] = {"ls", NULL};

    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd1, NULL), 0);
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd2, NULL), 1);
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd3, NULL), 0);
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd4, NULL), FAILURE);
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd5, NULL), 0);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

Test(execve, path_edge_cases, .init = redirect_all_std)
{
    params_t params = make_params();
    char *cmd[] = {"ls", NULL};

    change_value_env("PATH", &params.sh.envp, "");
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd, NULL), 84);
    change_value_env("PATH", &params.sh.envp, ":");
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd, NULL), 84);
    change_value_env("PATH", &params.sh.envp, "/bin");
    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd, NULL), 0);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

Test(command_handler, empty_input, .init = redirect_all_std)
{
    params_t params = make_params();

    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "", 0), SUCCESS);
    params.execs.curr_pid = 0;
    cr_assert_eq(command_handler(&params, "   ", 0), SUCCESS);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

Test(execve, return_values, .init = redirect_all_std)
{
    params_t params = make_params();
    char *cmd[] = {"ls", "nofile", NULL};

    params.execs.curr_pid = 0;
    cr_assert_eq(use_execve(&params, cmd, NULL), 2);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}
