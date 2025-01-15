/*
** EPITECH PROJECT, 2024
** my_libc
** File description:
** my_strchr
*/

#include "my_strings.h"

#include <stddef.h>

char *my_strchr(char *str, char c)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            return &str[i];
        i++;
    }
    return NULL;
}

char *my_strrchr(char *str, char c)
{
    int i = my_strlen(str);

    while (i >= 0) {
        if (str[i] == c)
            return &str[i];
        i--;
    }
    return NULL;
}
