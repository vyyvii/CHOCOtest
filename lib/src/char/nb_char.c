/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

/**
 * @ingroup char
 * @brief Search the string for a character in order to count it.
 * @param str String to search.
 * @param c Character to find.
 * @return The number of characters in the string.
 * @note Complexity: O(n)
 * @note Part of UtilsLib by Victor Defauchy.
 */
int nb_chars(char *str, char c)
{
    int cpt = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            cpt++;
    }
    return cpt;
}
