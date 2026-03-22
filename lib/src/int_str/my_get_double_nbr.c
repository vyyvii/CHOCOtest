/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

static int go_in_number(double *result, const char *str, int i)
{
    double factor = 0.1;

    while (str[i] >= '0' && str[i] <= '9') {
        *result = *result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.') {
        i++;
        while (str[i] >= '0' && str[i] <= '9') {
            *result += (str[i] - '0') * factor;
            factor *= 0.1;
            i++;
        }
    }
    return 1;
}

/**
 * @ingroup int_str
 * @brief Converts a string to a double (integer and fractional parts).
 * @param str Source string (optional '+'/'-' and one decimal point).
 * @return Converted double value.
 * @note Complexity: O(n)
 * @note Ignores any character after the valid numeric part.
 * @note Part of UtilsLib by Victor Defauchy.
 */
double my_get_double_nbr(char const *str)
{
    int i = 0;
    int sign = 1;
    double result = 0.0;

    if (!str)
        return 0.0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (str[i] < '0' || str[i] > '9')
        return 0.0;
    if (!go_in_number(&result, str, i))
        return 0.0;
    return result * sign;
}
