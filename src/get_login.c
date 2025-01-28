/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** get_login
*/

#include "my_sudo.h"

#include "my_strings.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static char *
find_user(FILE *file, int uid)
{
    char *line = NULL;
    char **tab = NULL;
    char *usr = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        tab = split_string(line, ":");
        if (!tab)
            return NULL;
        if (atoi(tab[2]) == uid) {
            usr = strdup(tab[0]);
            free(tab);
            break;
        }
        free(tab);
    }
    free(line);
    return usr;
}

char *
my_getlogin(void)
{
    int uid = getuid();
    FILE *file = fopen("/etc/passwd", "r");
    char *usr = NULL;

    if (file == NULL)
        return NULL;
    usr = find_user(file, uid);
    fclose(file);
    return usr;
}
