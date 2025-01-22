/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** get flags
*/

#include "my_sudo.h"

#include <stdlib.h>

void
check_arg(char *flag, flag_t *flags, int *i)
{
    for (int j = 1; flag[j]; j++){
        if (flag[j] == 'u'){
            flags->u = flag[j + 1] ? &flag[j + 1] : NULL;
            *i += 1;
        }
        if (flag[j] == 'g'){
            flags->g = flag[j + 1] ? &flag[j + 1] : NULL;
            *i += 1;
        }
        if (flag[j] == 'E'){
            flags->E = true;
            *i += 1;
        }
        if (flag[j] == 's'){
            flags->s = true;
            *i += 1;
        }
    }
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
            check_arg(av[i], flags, &i);
    return flags;
}
