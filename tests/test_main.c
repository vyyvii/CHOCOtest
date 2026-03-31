/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "tests.h"

char *capture_stdout(void (*func)(void))
{
    int pipefd[2];
    int saved_stdout;
    char buffer[4096];
    ssize_t size;

    pipe(pipefd);
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    func();
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    size = read(pipefd[0], buffer, sizeof(buffer) - 1);
    close(pipefd[0]);
    buffer[size] = '\0';
    return my_strdup(buffer);
}

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
    sh.last_path = NULL;
    params.sh = sh;
    reset_pipeline(&pipeline);
    params.execs = pipeline;
    params.execs.pids = malloc(sizeof(pid_t));
    params.execs.rdr = malloc(sizeof(redirection_t));
    params.execs.rdr[0].is = 0;
    return params;
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_command_handler),
        cmocka_unit_test(test_execve),
        cmocka_unit_test(test_copy_env),
        cmocka_unit_test(test_get_value_env),
        cmocka_unit_test(test_change_value_env),
        cmocka_unit_test(test_unset_value_env),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
