#include "ScienceExpressionCalculation.h"
#include "CalEngine/Rational.h"
#include "CalEngine/RationalMath.h"

#include "CalEngine/CalException.h"
namespace CalEngine
{


    ScienceExpressionCalculation::ScienceExpressionCalculation(QString inputExp)
        :AbstractExpressionCalculation(inputExp)
    {
        mOptPriority.insert('(',1);
        mOptPriority.insert('+', 2);
        mOptPriority.insert('-', 2);
        mOptPriority.insert('*', 3);
        mOptPriority.insert('/', 3);
        mOptPriority.insert('^', 4);
        mOptPriority.insert('s', 4);
        mOptPriority.insert('L', 4);
        mOptPriority.insert('p', 4);
        mOptPriority.insert('l', 4);
        mOptPriority.insert('!', 4);
    }

    QString ScienceExpressionCalculation::functionTranslate(const QString &inputStr)
    {

        QString res;
        int32_t n=inputStr.size();
        int cnt=0;//记录转换过的函数个数
        for(int32_t i=0;i<n;i++)
        {
            if(inputStr[i].isLetter())
            {
                QString optname;
                //提取符号
                int32_t j=0;
                for(j=i;j<n;j++)
                {
                    if(inputStr[j].isLetter())
                        optname.append(inputStr[j]);
                    else
                        break;
                }

                if(isOperator(optname))//如果是转换好的运算符
                {
                    res.append(optname);
                    continue;
                }

                if(j<n && inputStr[j]!='(')
                {
                    throw CalException(CalBracketError);
                }

                //开始转换
                if(optname=="sqrt")
                {
                    res.append(translateSqrt(inputStr,&j));
                }
                else if(optname=="pow")
                {
                    res.append(translatePow(inputStr,&j));
                }
                else if(optname=="log")
                {
                    res.append(translateLog(inputStr,&j));
                }
                else if(optname=="ln")
                {
                    res.append(translateLn(inputStr,&j));
                }
                else//运算符未命中
                {
                    throw CalException(CalOperatorError);
                }

                cnt++;
                i=j;//防止重复遍历
            }
            else
            {
                res.append(inputStr[i]);
            }
        }

        if(cnt!=0)
        {
            res=functionTranslate(res);
        }

        return res;
    }

    QString ScienceExpressionCalculation::translateSqrt(const QString &inputStr, int32_t *j)
    {
        QString res;
        int32_t n=inputStr.size();

        //记录位置
        int32_t dotpos=0,braLpos=*j,braRpos=0,branum=0;
        //逗号位置，左括号位置，右括号位置，括号数量
        for((*j)++;*j<n;(*j)++)
        {
            if(*j==n-1 && inputStr[*j]!=')')
            {
                throw CalException(CalBracketError);
            }
            else if(inputStr[*j]==',' && branum==0)
            {
                dotpos=*j;
            }
            else if(inputStr[*j]==')' && branum==0)
            {
                braRpos=*j;
                break;
            }
            else if(inputStr[*j]==')')
            {
                branum--;
            }
            else if(inputStr[*j]=='(')
            {
                branum++;
            }


        }
        //根据位置转换
        res.append("((");

        res.append(inputStr.mid(braLpos+1, dotpos-braLpos-1));
        res.append(")s(");

        res.append(inputStr.mid(dotpos+1, braRpos-dotpos-1));
        res.append("))");


        return res;

    }

    QString ScienceExpressionCalculation::translatePow(const QString &inputStr, int32_t *j)
    {

        QString res;
        int32_t n=inputStr.size();

        //记录位置
        int32_t dotpos=0,braLpos=*j,braRpos=0,branum=0;
        //逗号位置，左括号位置，右括号位置，括号数量
        for((*j)++;*j<n;(*j)++)
        {
            if(*j==n-1 && inputStr[*j]!=')')
            {
                throw CalException(CalBracketError);
            }
            else if(inputStr[*j]==',' && branum==0)
            {
                dotpos=*j;
            }
            else if(inputStr[*j]==')' && branum==0)
            {
                braRpos=*j;
                break;
            }
            else if(inputStr[*j]==')')
            {
                branum--;
            }
            else if(inputStr[*j]=='(')
            {
                branum++;
            }


        }
        //根据位置转换
        res.append("((");

        res.append(inputStr.mid(braLpos+1, dotpos-braLpos-1));
        res.append(")p(");

        res.append(inputStr.mid(dotpos+1, braRpos-dotpos-1));
        res.append("))");


        return res;
    }

    QString ScienceExpressionCalculation::translateLog(const QString &inputStr, int32_t *j)
    {

        QString res;
        int32_t n=inputStr.size();

        //记录位置
        int32_t dotpos=0,braLpos=*j,braRpos=0,branum=0;
        //逗号位置，左括号位置，右括号位置，括号数量
        for((*j)++;*j<n;(*j)++)
        {
            if(*j==n-1 && inputStr[*j]!=')')
            {
                throw CalException(CalBracketError);
            }
            else if(inputStr[*j]==',' && branum==0)
            {
                dotpos=*j;
            }
            else if(inputStr[*j]==')' && branum==0)
            {
                braRpos=*j;
                break;
            }
            else if(inputStr[*j]==')')
            {
                branum--;
            }
            else if(inputStr[*j]=='(')
            {
                branum++;
            }


        }
        //根据位置转换
        res.append("((");

        res.append(inputStr.mid(braLpos+1, dotpos-braLpos-1));
        res.append(")L(");

        res.append(inputStr.mid(dotpos+1, braRpos-dotpos-1));
        res.append("))");


        return res;
    }

    QString ScienceExpressionCalculation::translateLn(const QString &inputStr, int32_t *j)
    {
        QString res;
        int32_t n=inputStr.size();

        //记录位置
        int32_t braLpos=*j,braRpos=0,branum=0;
        //左括号位置，右括号位置，括号数量
        for((*j)++;*j<n;(*j)++)
        {
            if(*j==n-1 && inputStr[*j]!=')')
            {
                throw CalException(CalBracketError);
            }
            else if(inputStr[*j]==')' && branum==0)
            {
                braRpos=*j;
                break;
            }
            else if(inputStr[*j]==')')
            {
                branum--;
            }
            else if(inputStr[*j]=='(')
            {
                branum++;
            }

        }
        //根据位置转换
        res.append("((");

        res.append(inputStr.mid(braLpos+1, braRpos-braLpos-1));
        res.append(")l(");

        res.append("0))");


        return res;

    }

    bool ScienceExpressionCalculation::isOperator(const QString &inputalp)
    {
        if(inputalp=='+' || inputalp=='-' || inputalp=='*' || inputalp=='/' || inputalp=='^' || inputalp=='p' || inputalp=='s' || inputalp=='L' || inputalp=='!' || inputalp=='l')
            return true;
        return false;
    }

    QString ScienceExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)
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
            return (RationalMath::pow(A,B)).getNumber();
        if(opt=="L")
            return (RationalMath::log(A,B)).getNumber();
        if(opt=="l")
            return (RationalMath::ln(A)).getNumber();
        if(opt=="p")
            return (RationalMath::pow(A,B)).getNumber();
        if(opt=="s")
            return (RationalMath::sqrt(A,B)).getNumber();
        if(opt=="!")
            return (RationalMath::factorial(A)).getNumber();


        throw CalException(CalOperatorError);
    }

    void ScienceExpressionCalculation::preTreatment()
    {
        int32_t n=mExpression.size();
        for(int32_t i=0;i<n;i++)//负数和阶乘前面加零，e和pi换成数等操作
        {
            n=mExpression.size();
            if( (mExpression[i]=='-' && i==0) || (mExpression[i]=='-' && mExpression[i-1]=='(') )
            {
                mExpression.insert(i,'0');
            }
            else if(mExpression[i]=='!')
            {
                mExpression.insert(i+1,'0');
            }
            else if(mExpression[i]==L'π')
            {
                mExpression.replace(i,1,"(3.14159265358979323846)");
            }
            else if(mExpression[i]=='e' && (i==0 || i==n-1 || (!mExpression[i-1].isLetter() &&  !mExpression[i+1].isLetter())) )
            {
                mExpression.replace(i,1,"(2.71828182845904523536)");
            }
        }



        mExpression=functionTranslate(mExpression);
        QString asd=mExpression;

    }

}

