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
    int euid = my_geteuid(flags);

    if (setuid(euid) == -1)
        return 84;
    if (flags->s && !command)
        return execvp(shell, shell_argv);
    if (flags->E)
        return execvpe(command, args, env);
    return execvp(command, args);
}

static int
user_and_group_valid(flag_t *flags)
{
    FILE *file = fopen("/etc/group", "r");
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1){
        if (strstr(line, flags->usr) && strstr(line, flags->g)){
            free(line);
            fclose(file);
            return 1;
        }
    }
    free(line);
    fclose(file);
    return 0;
}

static void
print_user_group_error(flag_t *flags, char **args)
{
    char hostname[256] = {0};

    gethostname(hostname, 256);
    fprintf(stderr, "Sorry, user %s is not allowed to execute '", flags->usr);
    for (int i = 0; args[i]; i++) {
        if (args[i + 1] == NULL)
            fprintf(stderr, "%s", args[i]);
        else
            fprintf(stderr, "%s ", args[i]);
    }
    fprintf(stderr, "' as %s:%s on %s.\n", flags->usr, flags->g, hostname);
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
    if (!user_and_group_valid(flags)){
        print_user_group_error(flags, args);
        return 84;
    }
    if ((flags->u || flags->g) && (!flags->s && !command))
        return 84;
    return execute_command(flags, command, args, env);
}
