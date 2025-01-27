/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** authentication
*/
#define _GNU_SOURCE
#include "my_sudo.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <termios.h>

int
query_loop(char *passwd_hash, char *user)
{
    char *input = NULL;
    size_t size = 0;
    char *hash = NULL;

    for (int i = 0; i < 3; i++){
        printf("[my_sudo] password for %s: ", user);
        size = getline(&input, &size, stdin);
        if (!input)
            return 84;
        input[size - 1] = '\0';
        printf("\n");
        hash = crypt(input, passwd_hash);
        if (hash && strcmp(hash, passwd_hash) == 0){
            free(input);
            return 0;
        }
        printf("Sorry, try again.\n");
    }
    free(input);
    return 84;
}

int
auth(char *passwd_hash, char *user)
{
    struct termios oldt;
    struct termios newt;

    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &newt);
    if (query_loop(passwd_hash, user) == 0){
        tcsetattr(0, TCSANOW, &oldt);
        return 0;
    }
    tcsetattr(0, TCSANOW, &oldt);
    return 84;
}

int word_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

char *get_shell(char **env)
{
    char *shell = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], "SHELL=", 6) == 0) {
            shell = strdup(env[i] + 6);
            break;
        }
    }
    return shell;
}

int
authenticate_and_run(char *passwd_hash, flag_t *flags, char **av, char **env)
{
    int i = 1;
    char *command = NULL;
    char **args = NULL;
    char *shell = get_shell(env);
    char *shell_argv[] = { shell, NULL };

    for (; av[i] && av[i][0] == '-'; i++)
        if (strcmp(av[i], "-u") == 0)
            i++;
    command = av[i];
    args = &av[i];
    if (auth(passwd_hash, flags->u) == 84)
        return 84;
    if (flags->s && word_array_len(av) == 2)
        return execvp(shell, shell_argv);
    if (flags->E)
        return execvpe(command, args, env);
    return execvp(command, args);
}
