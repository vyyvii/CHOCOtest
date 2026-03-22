/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"


static char to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

/**
 * @ingroup str
 * @brief Compares two strings (lexicographic) but case has no impact.
 * @param s1 String 1.
 * @param s2 String 2.
 * @return 0 if equal, 1 if s1/S1>s2/S2, -1 otherwise.
 * @note Complexity: O(min(n, m))
 * @note Part of UtilsLib by Victor Defauchy.
 */
int my_strcmp_no_case(char *a, char *b)
{
    int i = 0;
    char ca = '\0';
    char cb = '\0';

    if (!a || !b)
        return (!a && !b) ? 1 : 0;
    while (a[i] && b[i]) {
        ca = to_lower(a[i]);
        cb = to_lower(b[i]);
        if (ca < cb)
            return -1;
        if (ca > cb)
            return 1;
        i++;
    }
    if (a[i] == b[i])
        return 0;
    return (a[i] < b[i]) ? -1 : 1;
}
