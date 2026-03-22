/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

void test_command_handler(void **state)
{
    params_t params = make_params();

    (void)state;
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "env", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "env too much", 0), FAILURE);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "setenv test test", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "setenv too much params", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "setenv 4AAA", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "setenv A-A", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "setenv", 0), SUCCESS);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "unsetenv test", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "unsetenv", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "unsetenv nothing", 0), SUCCESS);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "cd", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "cd ~", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "cd -", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "cd nowhere", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "cd too much", 0), FAILURE);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "thiscommanddoesnotexist", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "./thiscommanddoesnotexist", 0), FAILURE);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "ls nofile", 0), 2);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "ls", 0), 0);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "/bin/true", 0), 0);

    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "exit too much", 0), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(command_handler(&params, "exit", 0), SUCCESS);
    params.execs.curr_pid = 0;
    assert_int_equal(params.sh.loop, 0);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}

void test_execve(void **state)
{
    params_t params = make_params();
    char *cmd1[] = {"/bin/true", NULL};
    char *cmd2[] = {"/bin/false", NULL};
    char *cmd3[] = {"true", NULL};
    char *cmd4[] = {"thiscommanddoesnotexist", NULL};
    char *cmd5[] = {"ls", NULL};

    (void)state;
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd1, NULL), 0);
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd2, NULL), 1);
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd3, NULL), 0);
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd4, NULL), FAILURE);
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 0);
    change_value_env("PATH", &params.sh.envp, ":");
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 84);
    change_value_env("PATH", &params.sh.envp, "::");
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 84);
    change_value_env("PATH", &params.sh.envp, "/bin");
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 0);
    change_value_env("PATH", &params.sh.envp, ":/bin");
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 0);
    change_value_env("PATH", &params.sh.envp, "/bin:");
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 0);
    change_value_env("PATH", &params.sh.envp, ":/bin:");
    params.execs.curr_pid = 0;
    assert_int_equal(use_execve(&params, cmd5, NULL), 0);
    free_table((void **)params.sh.envp);
    free(params.execs.pids);
    free(params.execs.rdr);
}
