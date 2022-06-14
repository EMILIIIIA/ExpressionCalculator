#include "AbstractExpressionCalculation.h"
#include "CalEngine/Rational.h"
#include "CalEngine/CalException.h"

using CalEngine::Rational;


namespace CalEngine {
    //AbstractExpressionCalculation


    void AbstractExpressionCalculation::preTreatment()
    {
        int32_t n=mExpression.size();
        for(int32_t i=0;i<n;i++)//负数前面加零
        {
            if( (mExpression[i]=='-' && i==0) || (mExpression[i]=='-' && mExpression[i-1]=='(') )
            {
                mExpression.insert(i,'0');
            }
        }
    }

    AbstractExpressionCalculation::AbstractExpressionCalculation(QString inputExp)
    {
        mExpression=inputExp;
    }

    bool AbstractExpressionCalculation::legitimacyTest(const QString &input)//合法性检验
    {


        int n=input.size();//判断表达式长度
        int k=0;//用于括号检验

        for(int i=0;i<n;i++)
        {
            if(input[i] =='(') //如果是左括号
            {
                k++;
                if(i==n-1)
                {
                    throw CalException(CalBracketError);
                }//表达式末尾是左括号

                else if(input[i+1] ==')')//如果是空括号组“()”
                {
                    throw CalException(CalBracketError);
                }

                else if(i!=0 && input[i-1].isNumber())
                {
                    throw CalException(CalOperatorError);
                }
            }

            else if(input[i] ==')') //如果是右括号
            {k--;}

            if(k<0)
            {
                //一旦出现右括号数量大于左括号直接判错
                throw CalException(CalBracketError);
            }
        }

        //检查括号是否正确匹配
        if(k!=0)
        {
            throw CalException(CalBracketError);
        }

        for(int i=0;i<n;i++)
        {
            if(isOperator(input[i]))
            {
                if(i==n-1)//表达式末尾是运算符
                {
                    throw CalException(CalOperatorError);
                }

                else if(!( (input[i+1].isNumber()) ||input[i+1]=='(') )//运算符后必须是数字或左括号
                {
                    throw CalException(CalOperatorError);
                }//表达式“1++1”之类

                else if(i==0 || (!input[i-1].isNumber() && input[i-1]!=')') )
                {
                    throw CalException(CalOperatorError);
                }//运算符前不是数字或右括号或者为空

            }
        }

        //检测是否有未处理成功的函数
        for(int i=0;i<n;i++)
        {
            if(!isOperator(input[i]) && input[i].isLetter())
            {
                throw CalException(CalOperatorError);
            }
            if(input[i]==',')
            {
                throw CalException(CalOperatorError);
            }
        }

        return 1;//表达式无误
    }


    QQueue<QString> AbstractExpressionCalculation::infixToPostfix(const QString &input)//中缀转后缀
    {
        QString temNum; //用于后缀表达式
        QQueue<QString> res; //用于存储输出值
        QStack<QChar> opera; //用于存储运算符

        int n=input.size();
        for(int i=0;i<n;i++)//该循环负责将input栈内元素全部分类
        {
            if(input[i] ==' ') //如果是空格
            {
                i++; //跳过该字符
            }
            else if ((input[i]<='9' && input[i]>='0') || input[i]=='.') //如果是数字（"0~9"和"."）
            {
                temNum.append(input[i]);
            }
            else if(isOperator(input[i]))// 如果是运算符
            {
                if(!temNum.isEmpty())
                {
                    res.push_back(temNum);
                    temNum = "";
                }


                if(opera.empty())
                {
                    opera.push(input[i]);
                }
                else
                {
                    while(!opera.empty())
                    {
                        if(mOptPriority[opera.top()]>=mOptPriority[input[i]])
                        {
                            res.push_back(opera.pop());
                        }
                        else
                        {
                            break;
                        }
                    }
                    opera.push(input[i]);
                }
            }

            else if(input[i]=='(')
            {
                if(!temNum.isEmpty())
                {
                    res.push_back(temNum);
                    temNum="";
                }

                opera.push('(');
            }
            else if(input[i]==')')
            {
                if(!temNum.isEmpty())
                {
                    res.push_back(temNum);
                    temNum="";
                }

                QChar popedOpt;
                while(!opera.empty())
                {
                    popedOpt=opera.pop();
                    if(popedOpt=='(')
                        break;
                    res.push_back(popedOpt);
                }
            }
            else
            {
                return res;
            }
        }
        if(!temNum.isEmpty())
        {
            res.push_back(temNum);
            temNum="";
        }

        while(!opera.empty())
        {
            res.push_back(opera.pop());
        }
        return res;
    }

    QString AbstractExpressionCalculation::postfixEvaluation(QQueue<QString> inputExp)
    {
        QStack<Rational> calStack;
        for(QString &i:inputExp)
        {
            if(isOperator(i))
            {
                Rational numa,numb;
                QString numA=calStack.pop();
                QString numB=calStack.pop();
                calStack.push(doOperation(numA,numB,i));
            }
            else
            {
                calStack.push(i);
            }
        }
        return calStack.pop().getNumber();
    }

    QString AbstractExpressionCalculation::startCalculate(int32_t *success)
    {
        preTreatment();
        *success=legitimacyTest(mExpression);
        QString ans=postfixEvaluation(infixToPostfix(mExpression));
        return ans;
    }

};

