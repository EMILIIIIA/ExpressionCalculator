#include "ProgrammerExpressionCalculation.h"
#include "CalEngine/CalException.h"
namespace CalEngine
{

    ProgrammerExpressionCalculation::ProgrammerExpressionCalculation(QString inputExp,QString inputExpType)
        :AbstractExpressionCalculation(inputExp)
    {
        mOptPriority.insert('(',1);
        mOptPriority.insert('+', 2);
        mOptPriority.insert('-', 2);
        mOptPriority.insert('*', 3);
        mOptPriority.insert('/', 3);
        expType=inputExpType;
    }
    bool ProgrammerExpressionCalculation::isOperator(const QString &inputalp)
    {
        if(inputalp=='+' || inputalp=='-' || inputalp=='*' || inputalp=='/')
            return true;
        return false;
    }
    QString ProgrammerExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)
    {
        if(expType=="8")
        {
            int8_t A=numB.toLongLong(),B=numA.toLongLong();
            if(opt=="+")
                return QString::number(A+B);
            if(opt=="-")
                return QString::number(A-B);
            if(opt=="*")
                return QString::number(A*B);
            if(opt=="/")
                return QString::number(A/B);
        }
        if(expType=="16")
        {
            int16_t A=numB.toLongLong(),B=numA.toLongLong();
            if(opt=="+")
                return QString::number(A+B);
            if(opt=="-")
                return QString::number(A-B);
            if(opt=="*")
                return QString::number(A*B);
            if(opt=="/")
                return QString::number(A/B);
        }
        if(expType=="32")
        {
            int32_t A=numB.toLongLong(),B=numA.toLongLong();
            if(opt=="+")
                return QString::number(A+B);
            if(opt=="-")
                return QString::number(A-B);
            if(opt=="*")
                return QString::number(A*B);
            if(opt=="/")
                return QString::number(A/B);
        }
        if(expType=="64")
        {
            int64_t A=numB.toLongLong(),B=numA.toLongLong();
            if(opt=="+")
                return QString::number(A+B);
            if(opt=="-")
                return QString::number(A-B);
            if(opt=="*")
                return QString::number(A*B);
            if(opt=="/")
                return QString::number(A/B);
        }

        throw CalException(CalOperatorError);
    }

}
