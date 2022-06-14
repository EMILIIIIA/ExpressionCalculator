#include "NormalExpressionCalculation.h"

#include "CalEngine/Rational.h"
#include "CalEngine/RationalMath.h"
#include "CalEngine/CalException.h"
namespace CalEngine
{


    NormalExpressionCalculation::NormalExpressionCalculation(QString inputExp)
        :AbstractExpressionCalculation(inputExp)
    {
        mOptPriority.insert('(',1);
        mOptPriority.insert('+', 2);
        mOptPriority.insert('-', 2);
        mOptPriority.insert('*', 3);
        mOptPriority.insert('/', 3);
        mOptPriority.insert('^', 4);
    }
    bool NormalExpressionCalculation::isOperator(const QString &inputalp)
    {
        if(inputalp=='+' || inputalp=='-' || inputalp=='*' || inputalp=='/' || inputalp=='^')
            return true;
        return false;
    }

    QString NormalExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)
    {
        Rational A(numB),B(numA);

        if(opt=="+")
            return (A+B).getNumber();
        if(opt=="-")
            return (A-B).getNumber();
        if(opt=="*")
            return (A*B).getNumber();
        if(opt=="/")
            return (A/B).getNumber();
        if(opt=="^")
            return RationalMath::pow(A,B).getNumber();

        throw CalException(CalOperatorError);
    }
}

