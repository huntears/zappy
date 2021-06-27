/*
** EPITECH PROJECT, 2021
** MATH
** File description:
** Math header
*/

#ifndef MATH_H_
#define MATH_H_

#define ABS(x) ((x) >= 0 ? (x) : (-x))

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MIN3(x, y, z) MIN(MIN(x, y), z)

#define POW(x) ((x) * (x))
#define MOD(a, b) ((((a) % (int) (b)) + (int) (b)) % (int) (b))

#define GET_DIST_P(x1, x2) POW((x2) - (x1))

#define GET_DIST(x1, y1, x2, y2) (GET_DIST_P(x1, x2) + GET_DIST_P(y1, y2))

#define GET_TORUS_DIST(x1, y1, x2, y2, w, h)                                   \
    MIN3(GET_DIST_P(x1, x2), GET_DIST_P(x1, (x2) - (w)),                       \
        GET_DIST_P(x1, (x2) + (w)))                                            \
    +MIN3(GET_DIST_P(y1, y2), GET_DIST_P(y1, (y2) - (h)),                      \
        GET_DIST_P(y1, (y2) + (h)))

#endif /* !MATH_H_ */