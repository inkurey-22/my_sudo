/*
** EPITECH PROJECT, 2024
** c_proj_template
** File description:
** main
*/

#include <stdio.h>
#include <string.h>

#include "my_sudo.h"

void
print_usage(void)
{
    printf("usage: ./my_sudo -h\n");
    printf("usage: ./my_sudo [-ugEs] [command [args ...]]\n");
}

int
main(int ac, char **av)
{
    if (ac == 1){
        print_usage();
        return 84;
    }
    if (strcmp(av[1], "-h") == 0){
        print_usage();
        return 0;
    }
    return my_sudo(ac, av);
}
