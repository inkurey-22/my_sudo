/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** get flags
*/

#include "my_sudo.h"

#include "my_strings.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void
check_arg(char **av, flag_t *flags, int *i)
{
    if (strcmp(av[*i], "-u") == 0 && !check_flags(av[*i + 1], 1)){
        flags->u = strdup(av[*i + 1]);
        (*i)++;
    }
    if (strcmp(av[*i], "-g") == 0 && !check_flags(av[*i + 1], 2)){
        flags->g = strdup(av[*i + 1]);
        (*i)++;
    }
    if (strcmp(av[*i], "-E") == 0)
        flags->E = true;
    if (strcmp(av[*i], "-s") == 0)
        flags->s = true;
}

flag_t *
get_flags(int ac, char **av)
{
    flag_t *flags = malloc(sizeof(flag_t));

    flags->u = NULL;
    flags->g = NULL;
    flags->E = false;
    flags->s = false;
    for (int i = 1; i < ac; i++)
        if (av[i][0] == '-')
            check_arg(av, flags, &i);
    return flags;
}
