/*
** EPITECH PROJECT, 2026
** UtilisLib
** File description:
** The useful lib of VictorDfc
*/

#include "utilslib.h"

/**
 * @ingroup maths
 * @brief Return the factorial of a number.
 * @param nb The number.
 * @return The factorial of number.
 * @note COmplexity: log(nb)
 * @note Part of UtilsLib by Victor Defauchy.
 */
int my_factorial(int nb)
{
    return (nb == 0) ? 1 : nb * my_factorial(nb - 1);
}
