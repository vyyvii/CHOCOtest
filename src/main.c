/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** Write a UNIX command interpreter.
*/

#include "my.h"

int main(int ac, char **av, char **envp)
{
    (void)av;
    return minishell(ac, envp);
}
