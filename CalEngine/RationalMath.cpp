#include "CalEngine/RationalMath.h"

#include<QtMath>
#include<CalEngine/CalException.h>

namespace CalEngine
{
    const Rational RationalMath::math_pi("3.14159265358979323846");
    const Rational RationalMath::math_e("2.71828182845904523536");
    const Rational RationalMath::math_ln2("0.69314718055994530941723212145818");
    const Rational RationalMath::math_ln5("1.6094379124341003746007593332262");


    Rational RationalMath::abs(const Rational &A)
    {
        Rational Res=A;
        if(A.isNegative())
        {
            Res.setOppositeNumber();
        }
        return Res;
    }

    Rational RationalMath::ceil(const Rational &A)
    {
        Rational Res;
        if(A.getDecimal().size()==0)
        {
            Res.setNumber(A.getInteger());
        }
        else
        {
            Rational temparg=A+"1"_rat;
            Res.setNumber(temparg.getInteger());
        }
        return Res;
    }

    Rational RationalMath::floor(const Rational &A)
    {
        Rational Res;
        Res.setNumber(A.getInteger());
        return Res;
    }

    Rational RationalMath::pow(Rational A,int32_t n)
    {
        //典中典快速幂
        if(n<0)
        {
            return "1"_rat/pow(A,-n);
        }
        Rational Res("1");
        while(n)
        {
            if(n&1)
            {
                Res=Res*A;
                Res.setPrecision(20);
            }
            A=A*A;
            A.setPrecision(20);
            n>>=1;
        }
        return Res;
    }

    Rational RationalMath::exp(const Rational &A)
    {
        Rational Res("1");
        QString decimalPart=A.getDecimal();
        if(!decimalPart.isEmpty())
        {
            long double inp=decimalPart.toDouble();
            long double ans=qPow(2.71828182845904523536L,inp);
            Res=Res*Rational(ans);
        }

        int32_t integerPart=A.getInteger().toInt();
        Res=Res*RationalMath::pow(Rational("2.71828182845904523536"),integerPart);
        return Res;
    }

    Rational RationalMath::ln(const Rational &A)
    {
        if(A.isNegative() || A==Rational("0"))
        {
            throw CalException(CalParameterError);
        }
        //使用ln(a)=ln(b*2^n)，使得a小于根号2，以获得更高精度
        int32_t n=0;
        Rational B(A);
        while(B>Rational("1.4"))
        {
            n++;
            B=B/Rational("2");
            B.setPrecision(20);
        }

        long double res=qLn(B.getNumber().toDouble());
        return ( Rational("0.69314718055994")*Rational(n)+Rational(res) );
    }

    Rational RationalMath::log(const Rational &A,const Rational &B)
    {
        return RationalMath::ln(B)/RationalMath::ln(A);
    }

    Rational RationalMath::pow(const Rational &A,const Rational &B)
    {

        if(B<Rational("0"))//当乘方是负数
        {
            if(A==Rational("0"))
            {
                throw CalException(CalParameterError);
            }
            return "1"_rat/RationalMath::pow(A,B.getOppositeNumber());
        }

        if(B.getDecimal().size()==0)//当乘方是整数
        {
            return RationalMath::pow(A,B.getInteger().toInt());
        }

        if(B=="0")//当乘方为零
        {
            return Rational("0");
        }

        Rational ResInt,ResDec;
        ResInt=RationalMath::pow(A,B.getInteger().toInt());
        ResDec=Rational( qPow(A.getNumber().toDouble(),B.getDecimal().toDouble()) );
        return ResInt*ResDec;
    }

    Rational RationalMath::sqrt(const Rational &Base,const Rational &Exp)
    {
        return RationalMath::pow(Base,"1"_rat/Exp);
    }

    Rational RationalMath::factorial(const Rational &A)
    {
        if(!A.getDecimal().isEmpty() || A.isNegative())
        {
            throw CalException(ErrorName::CalParameterError);
        }

        if(A==Rational("0"))
        {
            return 0;
        }
        Rational B("1"),Res("1");
        for(;B<=A;B+=Rational("1"))
        {
            Res=Res*B;
        }
        return Res;
    }
}



