#ifndef RATIONAL_H_
#define RATIONAL_H_

/*
    Alexander Malyshev - rational.h

    A rational number is any number that can be represented in the form
    a/b where a,b are integers. This type is handy in that math operations
    on it are more accurate than that of simple doubles, and we can easily
    convert it to a double for convenience.


    Warnings: This is written for the x86-64 architecture (specifically
    rat_double2Rat), compiling for IA32 is a very bad idea. Use of
    rat_double2Rat is also discouraged, as some doubles (3.2) turn into
    very ugly rats.
*/

typedef struct {
    long num;
    long den;
} rat;

#define IS_NAN(r) ((r).den == 0)

/* for those that don't want to use "rat r = {1,2}" notation */
rat rat_create(long, long);

/* Standard arithmetic functions */
rat rat_add(rat, rat);
rat rat_sub(rat, rat);
rat rat_mult(rat, rat);
rat rat_div(rat, rat);

/* reciprocal */
rat rat_inv(rat);

/* simplifies the fraction */
rat rat_simp(rat);

/* auxiliary */
long rat_cmp(rat, rat);
void rat_print(rat);
void rat_println(rat);

/* converting between rats and doubles */
double rat_double(rat);
rat rat_double2Rat(double);

#endif
