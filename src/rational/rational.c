/** @file rational.c
 *  @brief A rational number library.
 *
 *  A simple implementation of a rational number. We pass in rat structs by
 *  value rather than by address for having neat and concise code, that and
 *  anyone trying to use this library for performance intensive math operations
 *  is barking up the wrong tree.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdio.h>
#include "rational.h"
#include "rational-int.h"

static const rat NaN = {0,0};

rat rat_create(long num, long den) {
    rat r;
    r.num = num;
    r.den = den;
    return r;
}

rat rat_add(rat r, rat s) {
    if (IS_NAN(r) || IS_NAN(s))
        return NaN;

    fix_rats(&r,&s);

    r.num = (r.num * s.den + s.num * r.den);
    r.den = (r.den * s.den);

    return rat_simp(r);
}

rat rat_sub(rat r, rat s) {
    s.num = 0 - s.num;
    return rat_add(r,s);
}

rat rat_mult(rat r, rat s) {
    long g;
    if (IS_NAN(r) || IS_NAN(s))
        return NaN;

    fix_rats(&r,&s);

    /* cross-simplify, helps against overflow */
    g = gcd(r.num, s.den);
    r.num /= g;
    s.den /= g;
    g = gcd(r.den, s.num);
    r.den /= g;
    s.num /= g;

    r.num *= s.num;
    r.den *= s.den;
    return rat_simp(r);
}

rat rat_div(rat r, rat s) {
    if (IS_NAN(s))
        return NaN;
    s = rat_inv(s);
    return rat_mult(r,s);
}

rat rat_inv(rat r) {
    long t;
    if (IS_NAN(r))
        return NaN;

    if (r.num < 0) {
        t = 0 - r.num;
        r.num = 0 - r.den;
        r.den = t;
    } else {
        t = r.num;
        r.num = r.den;
        r.den = t;
    }
    return r;
}

rat rat_simp(rat r) {
    long g;
    if (IS_NAN(r))
        return NaN;

    fix_rat(&r);

    g = gcd(r.num, r.den);
    r.num /= g;
    r.den /= g;
    return r;
}

long rat_cmp(rat r, rat s) {
    if (IS_NAN(r) || IS_NAN(s))
        return 1;

    r.num *= s.den;
    s.num *= r.den;
    return (r.num - s.num);
}

void rat_print(rat r) {
    if (IS_NAN(r))
        printf("NaN");
    else
        printf("%ld/%ld", r.num, r.den);
}

void rat_println(rat r) {
    rat_print(r);
    printf("\n");
}

double rat_double(rat r) {
    return ((double)r.num)/(r.den);
}

rat rat_double2Rat(double d) {
    rat r, s;
    long frac, exp, e;
    union {
        long u;
        double d;
    } a;

    a.d = d;
    frac = a.u;
    /* get out the mantissa and exp */
    frac &= ((1L << 52) - 1);
    exp = (a.u >> 52) & 0x7FF;
    /* if double is +/- inf or NaN, just return NaN */
    if (exp == 0x7FF)
        return NaN;
    /* subtract the bias to get e */
    e = exp - 1023;
    /* if |e| > 63 we can't represent it, its either too big or too small */
    if (e < -63 || e > 63)
        return NaN;
    /* if double is not denormalized, add back the leading 1 */
    if (exp != 0)
        frac |= (1L << 52);
    r.num = frac;
    r.den = (1L << 52);
    if (e < 0) {
        s.num = 1;
        s.den = (1 << (-e));
    } else {
        s.num = (1 << e);
        s.den = 1;
    }
    return rat_mult(r,s);
}

static void fix_rat(rat *r) {
    if (r->den < 0) {
        r->num = 0 - r->num;
        r->den = 0 - r->den;
    }
}

static void fix_rats(rat *r, rat *s) {
    fix_rat(r);
    fix_rat(s);
}

static long gcd(long x, long y) {
    long t;
    while (y != 0) {
        t = y;
        y = x % y;
        x = t;
    }
    return abs(x);
}

static long abs(long x) {
    return (x < 0 ? -x : x);
}
