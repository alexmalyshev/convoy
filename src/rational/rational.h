/** @file rational.h
 *  @brief Function prototypes and struct for a rational data type.
 *  
 *  Implementation of a rational number data type. A rational is a number
 *  of the form a/b, where a and b are both integers. Rationals that have
 *  a zero as their denominator are considered to be NaN. We maintain
 *  an invariant that rationals cannot have a negative denominator.
 *
 *  @author Alexander Malyshev
 *  @bug rat_double2Rat is written assuming Linux x86-64 types.
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

/** @brief A rational number. */
typedef struct {
    long num;   /**< numerator of the rational. */
    long den;   /**< denominator of the rational. */
} rat;

/** @brief Macro for checking if a rat is NaN. */
#define IS_NAN(r) ((r).den == 0)

/** @brief Creates a new rat.
 *
 *  For those that don't want to use "rat r = {1,2}" notation.
 *
 *  @param num the numerator of the rat.
 *  @param den the denominator of the rat.
 *  @return A new rat with numerator num and denominator den.
 */
rat rat_create(long num, long den);

/** @brief Adds two rats together.
 *
 *  Will return NaN if either r or s is NaN.
 *
 *  @param r a rational number.
 *  @param s a rational number.
 *  @return The sum of r and s.
 */
rat rat_add(rat r, rat s);

/** @brief Subtracts one rat from another.
 *
 *  Will return NaN if either r or s is NaN.
 *
 *  @param r a rational number.
 *  @param s a rational number.
 *  @return The difference between r and s.
 */
rat rat_sub(rat r, rat s);

/** @brief Multiplies two rats together.
 *
 *  Will return NaN if either r or s is NaN.
 *
 *  @param r a rational number.
 *  @param s a rational number.
 *  @return The product of r and s.
 */
rat rat_mult(rat r, rat s);

/** @brief Divides one rat by another.
 *
 *  Will return NaN if either r or s is NaN, or if s is zero.
 *
 *  @param r a rational number.
 *  @param s a rational number.
 *  @return The quotient of r and s.
 */
rat rat_div(rat r, rat s);

/** @brief Gives the reciprocal of a rat.
 *
 *  Will return NaN if r is NaN, or if r is zero.
 *
 *  @param r a rational number.
 *  @return The reciprocal of r.
 */
rat rat_inv(rat r);

/** @brief Puts a rat in simplest form.
 *
 *  Will return NaN if r is NaN.
 *
 *  @param r a rational number.
 *  @return The simplest form of r.
 */
rat rat_simp(rat r);

/** @brief Compares two rats.
 *
 *  Will return 1 if one of the rats is NaN.
 *
 *  @param r a rational number.
 *  @param s a rational number.
 *  @return An integer that is < 0 if r < s, > 0 if r > s, and = 0 if r == s.
 */
long rat_cmp(rat r, rat s);

/** @brief Prints out the rat to stdout without a newline.
 *
 *  Prints in the form "n/d", will print "NaN" if r is NaN.
 *
 *  @param r a rational number.
 *  @return Void.
 */
void rat_print(rat r);

/** @brief Prints out the rat to stdout with a newline.
 *
 *  Prints in the form "n/d", will print "NaN" if r is NaN.
 *
 *  @param r a rational number.
 *  @return Void.
 */
void rat_println(rat r);

/** @brief Converts a rat into a double.
 *
 *  If r is NaN, double will be inf if r.num > 0 and -inf if r.num < 0.
 *
 *  @param r a rational number.
 *  @return The double representation of r.
 */
double rat_double(rat r);

/** @brief Converts a double into a rat.
 *
 *  If the encoded exponent is < -63 or > 63, then the double cannot be
 *  represented as a rat (assuming that long is a 64bit type) and will
 *  return NaN.
 *
 *  @param d a double.
 *  @return The rational representation of d.
 */
rat rat_double2Rat(double d);

#endif /* RATIONAL_H_ */
