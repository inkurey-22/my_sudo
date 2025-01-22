/*
** EPITECH PROJECT, 2025
** mysudo
** File description:
** sudo.h
*/
#ifndef MY_SUDO_H_
    #define MY_SUDO_H_

    #include <stdbool.h>

typedef struct flag_s {
    char *u;
    char *g;
    bool E;
    bool s;
} flag_t;

int my_sudo(int ac, char **av);
int authenticate_and_run(char *passwd_hash, char *user, char **av);
flag_t *get_flags(int ac, char **av);

#endif /* !MY_SUDO_H_ */
