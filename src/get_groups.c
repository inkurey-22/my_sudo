/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** get_groups
*/

#include "my_sudo.h"

#include "my_strings.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void add_name_in_groups(char ***array, int *size, const char *new_element)
{
    *array = realloc(*array, (*size + 2) * sizeof(char *));
    if (*array == NULL) {
        perror("realloc failed");
        exit(84);
    }
    (*array)[*size] = strdup(new_element);
    if ((*array)[*size] == NULL) {
        perror("strdup failed");
        exit(84);
    }
    (*size)++;
    (*array)[*size] = NULL;
}

int user_in_group(char *user, char **tab)
{
    int len = 0;

    if (!tab || !tab[0])
        return 0;
    for (; tab[len] != NULL; len++);
    if (strstr(tab[len - 1], user))
        return 1;
    return 0;
}

static char **find_groups(FILE *file, char *user, char **groups_address)
{
    char *line = NULL;
    char **tab = NULL;
    int size = 0;
    char **groups = groups_address;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        tab = split_string(line, ":");
        if (!tab)
            continue;
        if (user_in_group(user, tab))
            add_name_in_groups(&groups, &size, tab[0]);
        my_free_word_array(tab);
    }
    free(line);
    return groups;
}

char **my_getgroups(char *user)
{
    FILE *file = fopen("/etc/group", "r");
    char **groups;

    if (!file)
        return NULL;
    groups = malloc(sizeof(char *));
    if (!groups)
        return NULL;
    groups[0] = NULL;
    groups = find_groups(file, user, groups);
    fclose(file);
    return groups;
}
