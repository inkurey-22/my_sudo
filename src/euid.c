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

int get_uid_from_name(char *name, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    int uid = 0;
    char *token = NULL;

    while (getline(&line, &len, file) != -1) {
        token = strtok(line, ":");
        free(line);
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
    FILE *file;
    int res = 0;

    if (flags->u) {
        file = fopen("/etc/passwd", "r");
        if (file == NULL)
            return res;
        res = get_uid_from_name(flags->u, file);
        fclose(file);
    }
    return res;
}
