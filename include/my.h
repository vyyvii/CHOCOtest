/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#ifndef MINISHELL_H
    #define MINISHELL_H
    #define _XOPEN_SOURCE 700
    #define SUCCESS 0
    #define OK 1
    #define FAILURE 84
    #include "utilslib.h"
    #include <signal.h>
    #include <dirent.h>
    #include <errno.h>
    #include <sys/wait.h>
    #include <sys/signalfd.h>

// === TYPEDEFS ===
typedef struct shell_s {
    int loop;
    char **envp;
    char *last_path;
} shell_t;

typedef struct redirection_s {
    int is;
    char *ordr;
    char *irdr;
    int addo;
    int addi;
    int effect_pid;
    int heredoc_fd[2];
} redirection_t;

typedef struct pipeline_ctx_s {
    int (*pipes)[2];
    int pipe_fail;
    int nb_pipes;
    pid_t *pids;
    int nb_pid;
    int curr_pid;
    redirection_t *rdr;
} pipeline_ctx_t;

typedef struct params_s {
    shell_t sh;
    pipeline_ctx_t execs;
} params_t;

typedef struct commands_s {
    char *command;
    int (*function)(params_t *, char **);
} commands_t;

typedef struct function_pipe_s {
    int (*function)(params_t *, char **);
    char **array;
} function_pipe_t;

// === FUNCTIONS ===
    // MAIN
int minishell(int ac, char **envp);

    // FREE_ALLOC       | ALLOCATION AND FREE
void free_pipeline(params_t *params);
void reset_pipeline(pipeline_ctx_t *pipeline);
params_t set_param(void);
int set_program(params_t *params, char **envp);
char **copy_env(char **envp);

    // PARSING          | PARSING FUNCTIONS
        // ALLOC_FREE_ERRORS
char **operators(params_t *params, char *input);
        // LOGIC
int redirection_operators(params_t *params, char **commands, int curr);
void save_heredoc(params_t *params, int curr);

    // CUT COMMAND      | SPECIFICS HELPERS
char **str_to_array(char *str);

    // ENV              | ENVIRONMENT FUNCTIONS
char *get_value_env(char *needle, char **haystack);
int change_value_env(char *needle, char ***haystack, char *change);
int unset_value_env(char *needle, char ***env);

    // COMMANDS         | EXECUTION OF A COMMAND (BUILTIN/PATH/FILE)
int command_handler(params_t *params, char *request, int i);
void errno_messages(char *cmd, int from_cd);

    // BUILTINS         | BUILTINS FUNCTIONS
int c_cd(params_t *params, char **command);
int c_env(params_t *params, char **command);
int c_setenv(params_t *params, char **command);
int c_unsetenv(params_t *params, char **command);
int c_exit(params_t *params, char **command);

    // EXECUTE          | CHILD & PARENTS PROCESS
        // CHILD
void child_process(params_t *params, char **command, char *comm,
    function_pipe_t *func);
        // PARENT
int use_execve(params_t *params, char **command, function_pipe_t *func);
int parents_process(pid_t pid);

#endif /* MINISHELL_H */
