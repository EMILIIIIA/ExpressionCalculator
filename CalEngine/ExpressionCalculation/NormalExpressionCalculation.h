#ifndef NORMALEXPRESSIONCALCULATION_H
#define NORMALEXPRESSIONCALCULATION_H

#include "AbstractExpressionCalculation.h"

namespace CalEngine
{
    class NormalExpressionCalculation:public AbstractExpressionCalculation
    {
    public:
        NormalExpressionCalculation(QString inputExp);
        bool isOperator(const QString &inputalpha)override;
        QString doOperation(const QString &numA,const QString &numB,const QString &opt)override;
    };
}
#endif // NORMALEXPRESSIONCALCULATION_H
