/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

/**
 * @ingroup str
 * @brief Tell if the string contain the char.
 * @param str String
 * @param c Character to test.
 * @return 1 if c if in str, 0 otherwise.
 * @note Complexity: O(n)
 * @note Part of UtilsLib by Victor Defauchy.
 */
int contains_char(char *str, char c)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            return 1;
    }
    return 0;
}

/**
 * @ingroup str
 * @brief Count the occurences of c in str.
 * @param str String
 * @param c Character to test.
 * @return Hte occurences of c in str
 * @note Complexity: O(n)
 * @note Part of UtilsLib by Victor Defauchy.
 */
int count_char(char *str, char c)
{
    int result = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            result++;
    }
    return result;
}
