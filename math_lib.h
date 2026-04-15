#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <limits.h>

namespace math_utils {
    inline int Add(int a, int b, bool &overflow) {
        if ((b > 0) && (a > INT_MAX - b)) {
            overflow = true;
            return 0;
        }
        if ((b < 0) && (a < INT_MIN - b)) {
            overflow = true;
            return 0;
        }
        return a + b;
    }

    inline int Sub(int a, int b, bool &overflow) {
        if ((b > 0) && (a < INT_MIN + b)) {
            overflow = true;
            return 0;
        }
        if ((b < 0) && (a > INT_MAX + b)) {
            overflow = true;
            return 0;
        }
        return a - b;
    }

    inline int Mul(int a, int b, bool &overflow) {
        if (a > 0 && b > 0 && a > INT_MAX / b) overflow = true;
        if (a > 0 && b < 0 && b < INT_MIN / a) overflow = true;
        if (a < 0 && b > 0 && a < INT_MIN / b) overflow = true;
        if (a < 0 && b < 0 && (a == INT_MIN || b == INT_MIN || -a > INT_MAX / -b)) overflow = true;

        if (overflow) return 0;
        return a * b;
    }

    inline int Div(int a, int b, bool &overflow) {
        if (b == 0) {
            overflow = true;
            return 0;
        }
        if (a == INT_MIN && b == -1) {
            overflow = true;
            return 0;
        }
        return a / b;
    }

    inline int Pow(int base, int exp, bool &overflow) {
        if (exp < 0) {
            overflow = true;
            return 0;
        }
        if (exp == 0){
            return 1;
        }

        int res = 1;
        for (int i = 0; i < exp; ++i) {
            res = Mul(res, base, overflow);
            if (overflow){
                return 0;
            }
        }
        return res;
    }

    inline int Fact(int n, bool &overflow) {
        if (n < 0) {
            overflow = true;
            return 0;
        }
        if (n == 0 || n == 1){
            return 1;
        }
        int prev = Fact(n - 1, overflow);
        if (overflow){
            return 0;
        }
        return Mul(n, prev, overflow);
    }

}

#endif
