/*
** EPITECH PROJECT, 2021
** TESTS_MOD
** File description:
** Test mod
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