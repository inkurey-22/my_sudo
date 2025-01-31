/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** run
*/
#define _GNU_SOURCE
#include "my_sudo.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int execute_command(flag_t *flags, char *command, char **args, char **env)
{
    char *shell = get_login_shell(flags->usr);
    char *shell_argv[] = {shell, NULL};

    if (setuid(my_geteuid(flags)) == -1)
            return 84;
    if (flags->s && !command)
        return execvp(shell, shell_argv);
    if (flags->E)
        return execvpe(command, args, env);
    return execvp(command, args);
}

int run(flag_t *flags, char **av, char **env)
{
    int i = 1;
    char *command = NULL;
    char **args = NULL;

    for (; av[i] && av[i][0] == '-'; i++)
        if (strcmp(av[i], "-u") == 0 || strcmp(av[i], "-g") == 0)
            i++;
    command = av[i];
    args = &av[i];
    if (!flags->s && !command)
        return 84;
    if (execute_command(flags, command, args, env) != 0)
        return 84;
    return 0;
}
