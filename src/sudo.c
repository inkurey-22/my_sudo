/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** main sudo file
*/

#include "my_sudo.h"

#include "my_strings.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

char *
get_usr_passwd(char *usr)
{
    FILE *file = fopen("/etc/shadow", "r");
    char *line = NULL;
    char *passwd_hash = NULL;
    size_t len = 0;
    char **tab = NULL;

    if (file == NULL)
        return NULL;
    while (getline(&line, &len, file) != -1) {
        if (strncmp(usr, line, strlen(usr)) == 0) {
            tab = split_string(line, ":");
            passwd_hash = strdup(tab[1]);
            free(tab);
            break;
        }
    }
    fclose(file);
    free(line);
    return passwd_hash;
}

char *
my_getlogin(char **env)
{
    char *login = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], "USERNAME=", 9) == 0) {
            login = strdup(env[i] + 9);
            break;
        }
    }
    return login;
}

int
my_sudo(int ac, char **av, char **env)
{
    flag_t *flags = get_flags(ac, av);
    char *passwd_hash = NULL;

    if (flags->u == NULL)
        flags->u = my_getlogin(env);
    if (flags->u == NULL)
        return 84;
    passwd_hash = get_usr_passwd(flags->u);
    if (passwd_hash == NULL)
        return 84;
    return authenticate_and_run(passwd_hash, flags, av, env);
}
