/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

/**
 * @ingroup str
 * @brief Tests if the string contains only lowercase letters.
 * @param str String.
 * @return 1 if lowercase only, otherwise 0.
 * @note Complexity: O(n)
 * @note Part of UtilsLib by Victor Defauchy.
 */
int my_str_islower(char const *str)
{
    if (!str)
        return 0;
    while (*str) {
        if (*str >= 97 && *str <= 122)
            str++;
        else
            return 0;
    }
    return 1;
}
