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

static char *get_user_or_group(int id)
{
    FILE *file = fopen("/etc/passwd", "r");
    char *line = NULL;
    size_t len = 0;
    char **tab = NULL;
    char *res = NULL;

    if (!file)
        return NULL;
    while (getline(&line, &len, file) != -1) {
        tab = split_string(line, ":");
        if (atoi(tab[2]) == id) {
            res = strdup(tab[0]);
            free(tab);
            break;
        }
        free(tab);
    }
    fclose(file);
    free(line);
    return res;
}

int is_id(char *str, char **groups, char *user)
{
    int id = 0;
    char *tmp = NULL;

    if ((str[0] < '0' || str[0] > '9') && str[0] != '%')
        return 0;
    id = str[0] == '%' ? atoi(str + 1) : atoi(str);
    tmp = get_user_or_group(id);
    if (is_user_or_group(tmp, user, groups))
        return 1;
    return 0;
}

static int get_perms(FILE *file, char *user, char **groups)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (line[0] == '\n' || strncmp(line, "Defaults", 8) == 0)
            continue;
        if (line[0] == '#' && is_id(line + 1, groups, user))
            return 0;
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
    if (strcmp(user, "root") == 0)
        return 0;
    res = get_perms(file, user, groups);
    fclose(file);
    if (res == 84)
        fprintf(stderr, "%s is not in the sudoers file.\n", user);
    return res;
}
