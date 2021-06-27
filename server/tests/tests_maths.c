/*
** EPITECH PROJECT, 2021
** TESTS_MATHS
** File description:
** Test maths
*/

#include <criterion/criterion.h>

#include "map.h"

Test(mod, positive_numbers)
{
    cr_expect_eq(MOD(0, 4), 0);
    cr_expect_eq(MOD(1, 4), 1);
    cr_expect_eq(MOD(2, 4), 2);
    cr_expect_eq(MOD(3, 4), 3);
    cr_expect_eq(MOD(4, 4), 0);
    cr_expect_eq(MOD(5, 4), 1);
    cr_expect_eq(MOD(6, 4), 2);
    cr_expect_eq(MOD(7, 4), 3);
    cr_expect_eq(MOD(8, 4), 0);
    cr_expect_eq(MOD(9, 4), 1);
    cr_expect_eq(MOD(10, 4), 2);
}

Test(mod, negative_numbers)
{
    cr_expect_eq(MOD(-1, 4), 3);
    cr_expect_eq(MOD(-2, 4), 2);
    cr_expect_eq(MOD(-3, 4), 1);
    cr_expect_eq(MOD(-4, 4), 0);
    cr_expect_eq(MOD(-5, 4), 3);
    cr_expect_eq(MOD(-6, 4), 2);
    cr_expect_eq(MOD(-7, 4), 1);
    cr_expect_eq(MOD(-8, 4), 0);
    cr_expect_eq(MOD(-9, 4), 3);
    cr_expect_eq(MOD(-10, 4), 2);
}

Test(abs, basic)
{
    cr_expect_eq(ABS(-1), 1);
    cr_expect_eq(ABS(0), 0);
    cr_expect_eq(ABS(1), 1);
}

Test(min, basic)
{
    cr_expect_eq(MIN(-1, 1), -1);
    cr_expect_eq(MIN(0, 1), 0);
    cr_expect_eq(MIN(1, 1), 1);
    cr_expect_eq(MIN(2, 1), 1);
}

Test(max, basic)
{
    cr_expect_eq(MAX(-1, 1), 1);
    cr_expect_eq(MAX(0, 1), 1);
    cr_expect_eq(MAX(1, 1), 1);
    cr_expect_eq(MAX(2, 1), 2);
}

Test(get_dist, basic)
{
    int base = GET_DIST(5, 2, 8, 1);

    cr_expect_eq(GET_DIST(5, 2, 8, 1), GET_DIST(5, 2, 8, 1));
    cr_expect_eq(GET_DIST(5, 2, 8, 1), GET_DIST(8, 1, 5, 2));
    for (int k = -10; k < 10; k++)
        cr_expect_eq(GET_DIST(5 + k, 2, 8 + k, 1), base);
    for (int k = -10; k < 10; k++)
        cr_expect_eq(GET_DIST(5, 2 + k, 8, 1 + k), base);
    for (int k = -10; k < 10; k++)
        cr_expect_eq(GET_DIST(5 + k, 2 + k, 8 + k, 1 + k), base);
}

Test(get_torus_dist, basic)
{
    int a1 = GET_TORUS_DIST(5, 2, 1, 8, 10, 15);
    int b1 = GET_TORUS_DIST(5, 2, 1, 8, 10, 15);
    int a2 = GET_TORUS_DIST(5, 2, 1, 8, 10, 15);
    int b2 = GET_TORUS_DIST(1, 8, 5, 2, 10, 15);

    cr_expect_eq(a1, b1);
    cr_expect_eq(a2, b2);
}

Test(get_torus_dist, basic_2)
{
    int base = GET_TORUS_DIST(5, 7, 5, 5, 10, 10);

    cr_expect_eq(GET_TORUS_DIST(7, 5, 5, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 7, 5, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 5, 7, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 5, 5, 7, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(3, 5, 5, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 3, 5, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 5, 3, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 5, 5, 3, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(7, 5, 15, 15, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 7, 15, 15, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 5, 17, 15, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(5, 5, 15, 17, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(17, 15, 5, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(15, 17, 5, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(15, 15, 7, 5, 10, 10), base);
    cr_expect_eq(GET_TORUS_DIST(15, 15, 5, 7, 10, 10), base);
}

Test(get_torus_dist, basic_3)
{
    int base = GET_TORUS_DIST(5, 7, 1, 8, 12, 15);

    for (int k = -50; k < 50; k++)
        cr_expect_eq(GET_TORUS_DIST(5 + k, 7, 1 + k, 8, 12, 15), base);
    for (int k = -50; k < 50; k++)
        cr_expect_eq(GET_TORUS_DIST(5, 7 + k, 1, 8 + k, 12, 15), base);
    for (int k = -50; k < 50; k++)
        cr_expect_eq(GET_TORUS_DIST(5 + k, 7 + k, 1 + k, 8 + k, 12, 15), base);
}