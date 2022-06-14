#ifndef RATIONALMATH_H
#define RATIONALMATH_H
#include "CalEngine/Rational.h"
namespace CalEngine {
    class RationalMath
    {
    public:
        static const Rational math_pi;
        static const Rational math_e;
        static const Rational math_ln2;
        static const Rational math_ln5;
        RationalMath();
        static Rational abs(const Rational &A);
        static Rational ceil(const Rational &A);
        static Rational floor(const Rational &A);
        static Rational pow(Rational A,int32_t n);
        static Rational pow(const Rational &A,const Rational &B);
        static Rational exp(const Rational &A);
        static Rational exp_decimal(const Rational &A);//浣跨敤娉板嫆灞曞紑璁＄畻exp灏忔暟閮ㄥ垎
        static Rational ln(const Rational &A);
        static Rational log(const Rational &A,const Rational &B);
        static Rational sqrt(const Rational &A);
        static Rational sqrt(const Rational &Base,const Rational &Exp);
        static Rational factorial(const Rational &A);
    };
}
#endif // RATIONALMATH_H
