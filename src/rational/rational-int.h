/** @file rational-int.h
 *  @brief Function prototypes for internal functions in the rational library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef RATIONAL_INT_H_
#define RATIONAL_INT_H_

/** @brief Maintains invariants of a rational number.
 *
 *  Never gets passed NULL or an address to a NaN.
 *
 *  @param r the address of the rat that we want to fix the invariants of.
 *  @return Void.
 */
static void fix_rat(rat *r);

/** @brief Maintains invariants of a rational number.
 *
 *  Never gets passed NULL or an address to a NaN.
 *
 *  @param r the address of a rat that we want to fix the invariants of.
 *  @param s the address of a rat that we want to fix the invariants of.
 *  @return Void.
 */
static void fix_rats(rat *r, rat *s);

/** @brief Computes the gcd of two integers.
 *
 *  x and y are both > 0.
 *
 *  @param x an integer.
 *  @param y an integer.
 *  @return The greatest common divisor of x and y.
 */
static long gcd(long x, long y);

#endif /* RATIONAL_INT_H_ */
