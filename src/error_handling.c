/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** error_handling
*/
#include "my_sudo.h"
#include "my_strings.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_name_valid(char *name, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    char **tab;

    while (getline(&line, &len, file) != -1) {
        if (!line || len == 0)
            continue;
        tab = split_string(line, ":");
        if (!tab || !tab[0])
            continue;
        if (strcmp(tab[0], name) == 0)
            return 0;
    }
    return 1;
}

int check_flags(char *str, int option)
{
    FILE *file;
    int res = 1;

    if (option != 1 && option != 2)
        return 0;
    if (option == 1)
        file = fopen("/etc/passwd", "r");
    if (option == 2)
        file = fopen("/etc/group", "r");
    res = is_name_valid(str, file);
    fclose(file);
    if (!file || res == 1) {
        if (option == 1)
            fprintf(stderr, "sudo: unknown user %s\n", str);
        if (option == 2)
            fprintf(stderr, "sudo: unknown group %s\n", str);
        exit(1);
    }
    return res;
}
