/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

/**
 * @ingroup maths
 * @brief Square root of a number.
 * @param nb Input double.
 * @return The square root of nb.
 * @note Complexity: O(sqrt(n))
 */
double my_sqrt(double nb)
{
    double x = nb;
    double prev = 0.0;

    if (nb <= 0.0)
        return 0.0;
    while (x != prev) {
        prev = x;
        x = 0.5 * (x + nb / x);
    }
    return x;
}
