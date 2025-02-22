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

int
my_sudo(int ac, char **av, char **env)
{
    flag_t *flags = get_flags(ac, av);
    char *passwd_hash = NULL;
    char **groups;

    flags->usr = my_getlogin();
    groups = my_getgroups(flags->usr);
    if (flags->usr == NULL)
        return 84;
    passwd_hash = get_usr_passwd(flags->usr);
    if (passwd_hash == NULL)
        return 84;
    if (auth(passwd_hash, flags->usr) || permissions(flags->usr, groups))
        return 84;
    return run(flags, av, env);
}
