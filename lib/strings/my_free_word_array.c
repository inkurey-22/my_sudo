/*
** EPITECH PROJECT, 2025
** c_proj_template
** File description:
** my_free_word_array
*/
#include <stdlib.h>
#include "my_strings.h"

void my_free_word_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
