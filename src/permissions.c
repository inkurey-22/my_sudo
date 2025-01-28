/*
** EPITECH PROJECT, 2025
** B-PSU-100-LIL-1-1-mysudo-theophile.riffe
** File description:
** sudoers_rights
*/

#include "my_sudo.h"
#include "my_strings.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int is_user_or_group(char *str, char *user, char **groups)
{
    if (strstr(str, user))
        return 1;
    for (int i = 0; groups[i] != NULL; i++) {
        if (strstr(str, groups[i]))
            return 1;
    }
    return 0;
}

static int get_perms(FILE *file, char *user, char **groups)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (line[0] == '#' || line[0] == '\n' ||
            strncmp(line, "Defaults", 8) == 0)
            continue;
        if (is_user_or_group(line, user, groups))
            return 0;
    }
    free(line);
    return 84;
}

int permissions(char *user, char **groups)
{
    FILE *file = fopen("/etc/sudoers", "r");
    int res = 0;

    if (!file)
        return 84;
    res = get_perms(file, user, groups);
    fclose(file);
    if (res == 84)
        fprintf(stderr, "%s is not in the sudoers file.\n", user);
    return res;
}
