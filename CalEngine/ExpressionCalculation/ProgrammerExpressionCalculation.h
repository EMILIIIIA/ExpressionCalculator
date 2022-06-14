#ifndef PROGRAMMEREXPRESSIONCALCULATION_H
#define PROGRAMMEREXPRESSIONCALCULATION_H

#include "AbstractExpressionCalculation.h"
namespace CalEngine
{


    class ProgrammerExpressionCalculation:public AbstractExpressionCalculation
    {
    private:
        QString expType;
    public:
        ProgrammerExpressionCalculation(QString inputExp,QString inputExpType);
        bool isOperator(const QString &inputalp)override;
        QString doOperation(const QString &numA,const QString &numB,const QString &opt)override;
    };


};


#endif // PROGRAMMEREXPRESSIONCALCULATION_H
