#ifndef EXPRESSIONCALCULATION_H
#define EXPRESSIONCALCULATION_H

#include <QStack>
#include <QHash>
#include <QQueue>

namespace CalEngine
{

    class AbstractExpressionCalculation
    {
    protected:
        QString mExpression;
        QHash<QChar,int32_t> mOptPriority;
        virtual void preTreatment();
    public:
        AbstractExpressionCalculation(QString inputExp);
        bool legitimacyTest (const QString &input);//合法性检验
        QQueue<QString> infixToPostfix(const QString &input);//中缀转后缀
        QString postfixEvaluation(QQueue<QString> input);//计算结果
        virtual QString startCalculate(int32_t* success);//外部调用
        virtual bool isOperator(const QString &inputalpha)=0;
        virtual QString doOperation(const QString &numA,const QString &numB,const QString &opt)=0;

    };


};
#endif // EXPRESSIONCALCULATION_H
