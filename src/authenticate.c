/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** authentication
*/

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

int
authenticate_and_run(char *passwd_hash, char *user, char **av)
{
    int i = 1;
    char *command = NULL;
    char **args = NULL;

    while (av[i] && av[i][0] == '-') {
        if (strcmp(av[i], "-u") == 0)
            i += 2;
        else
            i++;
    }
    command = av[i];
    args = &av[i];
    if (auth(passwd_hash, user) == 84)
        return 84;
    else
        execvp(command, args);
    return 0;
}
