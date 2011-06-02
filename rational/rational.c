#include <stdio.h>
#include "rational.h"
#include "rational-int.h"

static const rat RAT_UNKNOWN = {0,0};

/* rat_create - returns the rat with the given numerator and denominator */
rat rat_create(long num, long den) {
    rat r;
    r.num = num;
    r.den = den;
    return r;
}

/* rat_add - adds two rats together
 * Fails: r is NaN or s is NaN */
rat rat_add(rat r, rat s) {
    if (IS_NAN(r) || IS_NAN(s))
        return RAT_UNKNOWN;

    fix_rats(&r,&s);

    r.num = (r.num * s.den + s.num * r.den);
    r.den = (r.den * s.den);
    return rat_simp(r);
}

/* rat_sub - subtracts two rats
 * Fails: r is NaN or s is NaN */
rat rat_sub(rat r, rat s) {
    s.num *= -1;
    return rat_add(r,s);
}

/* rat_mult - multiplies two rats, done with slight
              inefficiency to guard against overflow
 * Fails: r is NaN or s is NaN */
rat rat_mult(rat r, rat s) {
    long g;
    if (IS_NAN(r) || IS_NAN(s))
        return RAT_UNKNOWN;

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

/* rat_div - divides one rat by another
 * Fails: r is NaN or s is NaN or s is zero */
rat rat_div(rat r, rat s) {
    if (IS_NAN(s))
        return RAT_UNKNOWN;
    s = rat_inv(s);
    return rat_mult(r,s);
}

/* rat_cmp - returns 0 if rats are equal, less than 0 if r < s and greater than
             0 if r > s. if one of the rats is NaN then we'll just return 1
 * Fails: s is NaN or r is NaN */
long rat_cmp(rat r, rat s) {
    if (IS_NAN(r) || IS_NAN(s))
        return 1;

    r.num *= s.den;
    s.num *= r.den;
    return (r.num - s.num);
}

/* rat_double - converts a rat into a double */
double rat_double(rat r) {
    return ((double)r.num)/(r.den);
}

/* rat_double2Rat - converts the given double into a rat.

                    Note: this function was specifically written for
                    architectures where long is a 64-bit type, no attempt was
                    made to make this work for systems where this is not the
                    case.
 * Fails: the encoded exponent in the double is less than -63 or greater than
          63 */
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
    /* if double is representation of INF or NAN, just return UNKNOWN rat */
    if (exp == 0x7FF)
        return RAT_UNKNOWN;
    /* subtract the bias to get e */
    e = exp - 1023;
    /* if |e| > 63 we can't represent it, its either too big or too small */
    if (e < -63 || e > 63)
        return RAT_UNKNOWN;
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

/* rat_print - prints out the rat to stdout, no newline */
void rat_print(rat r) {
    if (IS_NAN(r))
        printf("NaN");
    else
        printf("%ld/%ld", r.num, r.den);
}

/* rat_println - prints the rat to stdout and appends a newline */
void rat_println(rat r) {
    rat_print(r);
    putchar('\n');
}

/* rat_inv - returns the reciprocal of the given rat */
rat rat_inv(rat r) {
    long t;
    if (IS_NAN(r))
        return RAT_UNKNOWN;

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

/* rat_simp - puts the rat in simplest form
 * Fails: r is NaN */
rat rat_simp(rat r) {
    long g;
    if (IS_NAN(r))
        return RAT_UNKNOWN;

    fix_rat(&r);

    g = gcd(r.num, r.den);
    r.num /= g;
    r.den /= g;
    return r;   
}

/* fix_rat - maintains the invariant that the rat's denominator > 0
 * Invariant: r is not NULL, *r is not NaN */
static void fix_rat(rat *r) {
    if (r->den < 0) {
        r->num = 0 - r->num;
        r->den = 0 - r->den;
    }
}

/* fix_rats - makes sure both rats maintain denominator > 0 invariant
 * Invariant: r and s are not NULL, *r and *s are not NaN */
static void fix_rats(rat *r, rat *s) {
    fix_rat(r);
    fix_rat(s);
}

/* gcd - returns gcd of two longs
 * Invariant: x > 0, y > 0 */
static long gcd(long x, long y) {
    long t;
    while (y != 0) {
        t = y;
        y = x % y;
        x = t;
    }
    return x;
}
