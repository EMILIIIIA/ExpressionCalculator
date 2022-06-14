

# [ScienceExpressionCalculation](../index.md)

ExpressionCalculation实现了对表达式的分析与计算，包括了归一化处理、函数表达式识别与转换、表达式中缀转后缀，以及后缀表达式的计算。而ScienceExpressionCalculation是针对科学计算器进行适配的类，是AbstractExpressionCalculation的子类与实例化结果。

|**头文件**|**#include "ScienceExpressionCalculation.h"**|
|----|:-------|

## 公有成员

| **bool**    | **[*isOperator*(const QString &inputalpha)override](#isOperator)** |
|----|:-------|
|**QString**|**[*doOperation*(const QString &numA,const QString &numB,const QString &opt)override](#doOperation)**|

## 私有成员

| **QString** | **[functionTranslate(const QString &inputStr)](#functionTranslate)** |
| ----------- | :----------------------------------------------------------- |
| **QString** | **[translateSqrt(const QString &inputStr,int32_t *j)](#translateSqrt)** |
| **QString** | **[translatePow(const QString &inputStr,int32_t *j)](#translatePow)** |
| **QString** | **[translateLog(const QString &inputStr,int32_t *j)](#translateLog)** |
| **QString** | **[translateLn(const QString &inputStr,int32_t *j)](#translateLn)** |
| **void**    | **[*preTreatment*()override](#preTreatment)**                |

## 详细描述

本类是AbstractExpressionCalculation类对于科学计算器的子类，用于针对科学计算器进行运算。其中需要在父类中重载的函数为***isOperator***、***doOperation***和***preTreatment***。



## 成员函数文档

<span id="ScienceExpressionCalculation"></span>

### ScienceExpressionCalculation::ScienceExpressionCalculation(QString inputExp):AbstractExpressionCalculation(inputExp)

构造函数，传入表达式，同时对运算符优先级进行赋值。

举例：

```c++
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
```

##

<span id="functionTranslate"></span>

### QString ScienceExpressionCalculation::functionTranslate(const QString &inputStr)

函数转换函数。由于在表达式中缀转后缀与计算的过程中，表达式需要为“运算符A 运算符 运算数B”的形式（二元运算表达式），因此在此函数中将会将数学函数归一化为上述形式。识别到对应函数的字符时，调用具体的函数转换函数，对该函数进行转换，将原函数转换结果为上述形式，进而继续进行后续计算。

##

<span id="translateSqrt"></span>

### QString ScienceExpressionCalculation::translateSqrt(const QString &inputStr, int32_t *j)

开方函数转换，sqrt(A,B)转换为 A s B。

##

<span id="translateLog"></span>

###  QString ScienceExpressionCalculation::translateLog(const QString &inputStr, int32_t *j)

对数函数转换，log(A,B)转换为 A L B。

##

<span id="translateLn"></span>

### QString ScienceExpressionCalculation::translateLn(const QString &inputStr, int32_t *j)

自然对数函数转换，ln(A)转换为 A l 0(l为小写L)，其中0是为了保证“运算符A 运算符 运算数B”格式而设计的占位符，实际运算中并不需要。

##

<span id="translatePow"></span>

### QString ScienceExpressionCalculation::translatePow(const QString &inputStr, int32_t *j)

指数函数转换，pow(A,B)转换为 A p B。

##

<span id="isOperator"></span>

### bool ScienceExpressionCalculation::isOperator(const QString &inputalp)

判断输入字符是否为运算符。其中普通计算器中含有：“ + ”、“ - ”、“ * ”、“ / ”、 “ ^ ”、“ p ”、“ s ”、“ L ”、 “ ! ”和“ l ”共9种运算符。

举例：

```c++
 bool ScienceExpressionCalculation::isOperator(const QString &inputalp)
{
    if(inputalp=='+' || inputalp=='-' || inputalp=='*' || inputalp=='/' || inputalp=='^' || inputalp=='p' || inputalp=='s' || inputalp=='L' || inputalp=='!' || inputalp=='l')
        return true;
    return false;
}

```

##

<span id="doOperation"></span>

### QString ScienceExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)

根据运算符进行相应的运算。

举例：

```c++
QString ScienceExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)
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
        return (RantionalMath::pow(A,B)).getNumber();
    if(opt=="L")
        return (RantionalMath::log(A,B)).getNumber();
    if(opt=="l")
        return (RantionalMath::ln(A)).getNumber();
    if(opt=="p")
        return (RantionalMath::pow(A,B)).getNumber();
    if(opt=="s")
        return (RantionalMath::sqrt(A,B)).getNumber();
    if(opt=="!")
        return (RantionalMath::factorial(A)).getNumber();

    throw CalException(CalOperatorError);
}
```
}

##

<span id="preTreatment"></span>

###  void ScienceExpressionCalculation::preTreatment()

- 对负数进行预处理，在识别到负数时，该函数会在负数前补充“0”，使负数变为一个减法算式。
- 在阶乘符号!后补0，使阶乘符号转换成二元运算符，保证了“运算符A 运算符 运算数B”的格式。

- 对特定科学数字进行识别与赋值：

  - e = 2.71828182845904523536

  - π = 3.14159265358979323846

- 调用[functionTranslate()](#functionTranslate)函数，进行数学函数处理。