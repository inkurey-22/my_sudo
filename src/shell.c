/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** shell
*/

#include "my_sudo.h"

#include "my_strings.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *
get_login_shell(char *usr)
{
    FILE *file = fopen("/etc/passwd", "r");
    char *line = NULL;
    char *shell = NULL;
    size_t len = 0;

    if (file == NULL)
        return NULL;
    while (getline(&line, &len, file) != -1) {
        if (strncmp(usr, line, strlen(usr)) == 0) {
            shell = strdup(strrchr(line, ':') + 1);
            shell[strlen(shell) - 1] = '\0';
            break;
        }
    }
    fclose(file);
    free(line);
    return shell;
}
