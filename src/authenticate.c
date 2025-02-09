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

static void
print_bad_password(int i)
{
    if (i == 2)
        printf("sudo: 3 incorrect password attempts\n");
    else
        printf("Sorry, try again.\n");
}

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
        print_bad_password(i);
    }
    free(input);
    return 84;
}

int auth(char *passwd_hash, char *user)
{
    struct termios oldt;
    struct termios newt;

    if (strcmp(user, "root") == 0)
        return 0;
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
