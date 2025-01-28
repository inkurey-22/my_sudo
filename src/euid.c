/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** euid
*/

#include "my_sudo.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
get_uid_from_name(char *name)
{
    char *line = NULL;
    FILE *file = fopen("/etc/passwd", "r");
    size_t len = 0;
    int uid = 0;
    char *token = NULL;

    if (file == NULL)
        return 0;
    while (getline(&line, &len, file) != -1) {
        token = strtok(line, ":");
        if (token && strcmp(token, name) == 0) {
            strtok(NULL, ":");
            token = strtok(NULL, ":");
            uid = atoi(token);
            break;
        }
    }
    fclose(file);
    free(line);
    return uid;
}

int
my_geteuid(flag_t *flags)
{
    if (flags->u)
        return get_uid_from_name(flags->u);
    return 0;
}
