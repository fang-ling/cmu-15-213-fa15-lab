/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /* x ^ y = (x | y) & (~x | ~y)
     *       = ~~ ((x | y) & (~x | ~y))
     *       = ~ (~(x | y) | ~(~x | ~y))
     *       = ~ ((~x & ~y) | (x & y))
     *       = ~(~x & ~y) & ~(x & y)
     */
    return ~(~x & ~y) & ~(x & y);
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /* minimum two's complement integer is:
     *          0b1000........000
     *             \--31 zeros--/
     */
    return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /* If x is the maximum, two's complement number, then x should be
     *          0b0111.......111
     *             \--31 ones--/
     * that's to say: x + 1 == ~x.
     * However, 0b11111..111111 also satisfy this equation. We need to
     *            \--32 ones--/
     * exclude this kind of possibility. Since 0b11111..111111 = (~1) + 1.
     */
    return !((x + 1) ^ (~x)) & !!(x ^ ((~1) + 1));
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int mask = 0xaa; /* 0b10101010 */
    mask <<= 8; mask += 0xaa;
    mask <<= 8;	mask +=	0xaa;
    mask <<= 8;	mask +=	0xaa;

    /* mask is now all odd-numbered bits in word set to 1.
     * i.e. 0b10101010101010101010101010101010
     */
    return !(mask ^ (x & mask));
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return (~x) + 1;
}
//3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    int least_sig_four_bits = x & 0xf;
    int minus_1 = ~1 + 1;
    int minus_9 = ~9 + 1;
    /* check if least significant four bits is less than 0x9,
     * if so, then (`least_sig_four_bits` + `minus_9`) will always result -1.
     * (Performs right shifts arithmetically.)
     */
    int diff = (least_sig_four_bits + minus_9) >> 31;
    return !((x >> 4) ^ 0x3) & !((least_sig_four_bits ^ 0x9) &
                                 (diff ^ minus_1));
    /*             ???
     * check first four bits equal 0x3
     *
     */
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int minus_1 = ~1 + 1;
    /* !x is the same as x == 0
     * if x == 0, then is_x_true = -1 (all bits set to one)
     * else is_x_true = 0;
     */
    int is_x_true = !x + minus_1;
    return (is_x_true & y) | (~is_x_true & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /* = 1 when the signs are different (by comparing the most significant bit)
     */
    int is_diff_sign = !!((x >> 31) ^ (y >> 31));
    int x_negative_y_positive = is_diff_sign & (x >> 31);
    /* check if is the same sign and compare the magnitude (y - x) */
    int is_less = !is_diff_sign & !((y + (~x + 1)) >> 31);
    return x_negative_y_positive | is_less;
}
//4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    /* if x == 0, then both (x >> 31) and (~x + 1) >> 31) equal zero.
     * else either (x >> 31) or (~x + 1) >> 31) is all bits set to one,
     * i.e. it equals -1.
     */
    return ((x >> 31) | ((~x + 1) >> 31)) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /* dlc require this, :-( */
    int sign, bit16, bit8, bit4, bit2, bit1;

    sign = x >> 31;
    /* Get rid of negative sign if x < 0.
     * Ex:                     x = -1234567 (-0b100101101011010000111)
     * (sign & ~x) | (~sign & x) =  1234566 ( 0b100101101011010000110)
     */
    x = (sign & ~x) | (~sign & x);
    bit16 = !!(x >> 16) << 4;
    x = x >> bit16;
    bit8 = !!(x >> 8) << 3;
    x = x >> bit8;
    bit4 = !!(x >> 4) << 2;
    x = x >> bit4;
    bit2 = !!(x >> 2) << 1;
    x = x >> bit2;
    bit1 = !!(x >> 1);
    x = x >> bit1;

    return bit16 + bit8 + bit4 + bit2 + bit1 + x + 1;
}
//float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int exp_and_sign = 0;
    int frac = 0;

    if (((0xff << 23) & uf) == (0xff << 23)) {
        return uf;
    } else if (uf == 0) {
        return 0;
    } else if (uf == 0x80000000) {
        return uf;
    } else if (uf == 1) {
        return 2;
    }
    if (((uf >> 23) & 0x7) == 0) {
        exp_and_sign = (uf >> 23) << 23;
        frac = uf & 0x7fffff;
        frac *= 2;
    } else {
        exp_and_sign = ((uf >> 23) + 1) << 23;
        frac = uf & 0x7fffff;
    }

    return exp_and_sign + frac;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    /* 8 exponent bits */
    int exp = (uf >> 23) & 0xFF;
    /* 23 fraction bits */
    int frac = uf & 0x7FFFFF;
    /* amount to shift normalized values by (bias of 127) */
    int e = exp - 127;

    /* returns if NaN */
    if (exp == 0x7F800000) {
        return 0x80000000u;
    }
    /* rounds down to zero if exponent is zero */
    if (!exp) {
        return 0;
    }
    /* rounds down to zero if there are no left shifts */
    if (e < 0) {
        return 0;
    }
    /* return if out of range for ints */
    if (e > 30) {
        return 0x80000000u;
    }
    /* normalized, append a 1 to the left of the frac */
    frac = frac | 0x800000;
    if (e >= 23) { /* shift left if shift > 23 */
        frac = frac << (e-23);
    } else { /* else we need to shift right */
        frac = frac >> (23 -e);
    }
    /* return negated value if sign bit is 1 */
    if ((uf >> 31) & 1) {
        return ~frac + 1;
    }
    return frac;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    unsigned int exp;
    unsigned int frac;
    if (x < -149) {
        return 0;
    }
    /* denormalized */
    if (x < -126 && x >= -149) {
        frac =  1 << (23 + x + 126);
        return frac;
    }
    if (x >= -126 && x <= 127) {
        exp = (x + 127) << 23;
        return exp;
    }
    /* inf */
    if (x > 127) {
        return 0xFF << 23;
    }
    return 0;
}
