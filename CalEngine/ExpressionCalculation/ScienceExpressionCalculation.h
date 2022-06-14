#ifndef SCIENCEEXPRESSIONCALCULATION_H
#define SCIENCEEXPRESSIONCALCULATION_H

#include"AbstractExpressionCalculation.h"

namespace CalEngine
{
    class ScienceExpressionCalculation:public AbstractExpressionCalculation
    {
    protected:
        QString functionTranslate(const QString &inputStr);
        QString translateSqrt(const QString &inputStr,int32_t *j);
        QString translatePow(const QString &inputStr,int32_t *j);
        QString translateLog(const QString &inputStr,int32_t *j);
        QString translateLn(const QString &inputStr,int32_t *j);
        void preTreatment()override;
    public:
        ScienceExpressionCalculation(QString inputExp);
        bool isOperator(const QString &inputalpha)override;
        QString doOperation(const QString &numA,const QString &numB,const QString &opt)override;

    };
}
#endif // SCIENCEEXPRESSIONCALCULATION_H
