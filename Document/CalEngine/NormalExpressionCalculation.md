# [NormalExpressionCalculation](../index.md)
ExpressionCalculation实现了对表达式的分析与计算，包括了归一化处理、函数表达式识别与转换、表达式中缀转后缀，以及后缀表达式的计算。而NormalExpressionCalculation是针对普通计算器进行适配的类，是AbstractExpressionCalculation的子类与实例化结果。

| **头文件** | **#include "NormalExpressionCalculation.h"** |
| ---------- | :------------------------------------------- |

## 公有成员

| **bool**    | **[*isOperator*(const QString &inputalpha)override](#isOperator)**                                    |
| ----------- | :---------------------------------------------------------------------------------------------------- |
| **QString** | **[*doOperation*(const QString &numA,const QString &numB,const QString &opt)override](#doOperation)** |

## 

## 详细描述
本类是AbstractExpressionCalculation类对于普通计算器的子类，用于针对普通计算器进行运算。其中需要在父类中重载的函数为***isOperator***和***doOperation***。



## 成员函数文档

<span id="NormalExpressionCalculation"></span>

### NormalExpressionCalculation::NormalExpressionCalculation(QString inputExp):AbstractExpressionCalculation(inputExp)
构造函数，传入表达式，同时对运算符优先级进行赋值。

举例：

```c++
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

```

##

<span id="isOperator"></span>

### bool NormalExpressionCalculation::isOperator(const QString &inputalp)

判断输入字符是否为运算符。其中普通计算器中含有：“ + ”、“ - ”、“ * ”、“ / ”和 “ ^ ”共五种运算符。

举例：

```c++
bool NormalExpressionCalculation::isOperator(const QString &inputalp)
{
    if(inputalp=='+' || inputalp=='-' || inputalp=='*' || inputalp=='/' || inputalp=='^')
        return true;
    return false;
}

```

##

<span id="doOperation"></span>

### QString NormalExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)

根据运算符进行相应的运算。

举例：

```c++
QString NormalExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)
{
    Rantional A(numB),B(numA);

    if(opt=="+")
        return (A+B).getNumber();
    if(opt=="-")
        return (A-B).getNumber();
    if(opt=="*")
        return (A*B).getNumber();
    if(opt=="/")
        return (A/B).getNumber();
    if(opt=="^")
        return RantionalMath::pow(A,B).getNumber();

    throw CalException(CalOperatorError);
}
```