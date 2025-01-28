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
    char *usr;
    char *u;
    char *g;
    bool E;
    bool s;
} flag_t;

int my_sudo(int, char **, char **);
int authenticate_and_run(char *, flag_t *, char **, char **);
flag_t *get_flags(int, char **);

char *my_getlogin(void);
char *get_login_shell(char *);
int my_geteuid(flag_t *);

#endif /* !MY_SUDO_H_ */
