/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

/**
 * @ingroup str
 * @brief Tests if the string contains only alphanumerics characters
 * A-Z/a-z/0-9/_.
 * @param str String.
 * @return 1 if alphanumeric only, otherwise 0.
 * @note Complexity: O(n)
 * @note Part of UtilsLib by Victor Defauchy.
 */
int my_str_isalphanumeric(char const *str)
{
    if (!str)
        return 0;
    while (*str) {
        if ((*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122)
            || *str == 95 || (*str >= 48 && *str <= 57))
            str++;
        else
            return 0;
    }
    return 1;
}
