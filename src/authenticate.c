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

char *
get_salt(char *passwd_hash)
{
    char *salt = malloc(strlen(passwd_hash) + 1);
    if (!salt)
        return NULL;

    int dollar_count = 0;
    for (int i = 0; passwd_hash[i] != '\0'; i++) {
        if (passwd_hash[i] == '$') {
            dollar_count++;
            if (dollar_count == 4) {
                salt[i + 1] = '\0';
                break;
            }
        }
        salt[i] = passwd_hash[i];
    }
    return salt;
}

int
auth(char *passwd_hash, char *user)
{
    char *input = NULL;
    struct termios oldt;
    struct termios newt;
    size_t size = 0;
    char *hash = NULL;
    char *salt = get_salt(passwd_hash);

    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &newt);
    for (int i = 0; i < 3; i++){
        printf("[my_sudo] password for %s: ", user);
        size = getline(&input, &size, stdin);
        if (!input)
            return 84;
        input[size - 1] = '\0';
        printf("\n");
        hash = crypt(input, passwd_hash);
        if (hash && strcmp(hash, passwd_hash) == 0){
            tcsetattr(0, TCSANOW, &oldt);
            free(input);
            return 0;
        }
        printf("Sorry, try again.\n");
    }
    tcsetattr(0, TCSANOW, &oldt);
    free(input);
    return 84;
}

int
authenticate_and_run(char *passwd_hash, char *user, char **av)
{
    if (auth(passwd_hash, user) == 84)
        return 84;
    if (av[2] != NULL)
        return execlp(av[1], av[1], &av[1], NULL);
    else
        return execlp(av[1], av[1], NULL);
}
