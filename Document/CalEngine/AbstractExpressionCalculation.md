# [AbstractExpressionCalculation](../index.md)
ExpressionCalculation实现了对表达式的分析与计算，包括了归一化处理、函数表达式识别与转换、表达式中缀转后缀，以及后缀表达式的计算。同时，此类还针对普通计算器和科学型计算器进行了区别与适配。

|**头文件**|**#include "AbstractExpressionCalculation.h"**|
|----|:-------|

## 公有成员

|**bool**|**[legitimacyTest (const QString &input)](#legitimacyTest)**|
|----|:-------|
|**QQueue<QString\>**|**[infixToPostfix(const QString &input)](#infixToPostfix)**|
|**QString**|**[postfixEvaluation(QQueue<QString\> input)](#postfixEvaluation)**|
|**virtual QString**|**[*startCalculate*(int32_t* success)](#startCalculate)**|
|**virtual bool**|**[*isOperator*(const QString &inputalpha)=0](#isOperator)**|
|**virtual QString**|**[*doOperation*(const QString &numA,const QString &numB,const QString &opt)=0](#doOperation)**|

## 私有成员

| **virtual void** | ***[preTreatment( )](#preTreatment)*** |
|----|:-------|

## 私有变量

| 变量名           | 含义                 |
| ---------------- | :------------------- |
| **mExpression**  | **存储输入的表达式** |
| **mOptPriority** | **运算符优先级赋值** |

**注意事项：** 变量**mOptPriority**决定了数学表达式中不同运算符的优先级，由于不同种类计算器中运算符均不同，所以该变量需要在具体的子类构造函数中进行赋值，赋值后所定义的值将以哈希值的形式存储于变量中。



## 详细描述

本类是表达式计算中对应[NormalExpressionCalculation](./NormalExpressionCalculation)和[ScienceExpressionCalculation](./ScienceExpressionCalculation)创建的抽象类，它所有的虚函数都可以有选择性的在子类中重写，用于针对性的实例化子类。当实例化子类时，抽象类也会跟随着实例化。

由于在普通计算器与科学计算器中运算符定义不同（科学计算器中包含sin、log等函数的识别、处理与运算），故二者的***isOperator***函数与***doOperation***函数内容出现差异。如果我们以科学计算器的函数为准，在使用普通计算器时就会造成大量不必要的资源开销；同时普通计算器又无法满足其他计算器的计算需求，再加上我们需要为今后可能加入的其他类型计算器（程序员型等）留出接口，所以我们将该类设为虚函数，作为所有类型计算器的父类。在使用具体类型计算器时，AbstractExpressionCalculation类会对出现不同定义的函数进行重载，极大的节省了资源开销，同时减少了大量重复的代码。



## 成员函数文档

<span id="AbstractExpressionCalculation"></span>

### AbstractExpressionCalculation::AbstractExpressionCalculation(QString inputExp)
构造函数，同时存入输入表达式。

举例：

```c++
AbstractExpressionCalculation::AbstractExpressionCalculation(QString inputExp)
{
    mExpression=inputExp;
}
```

##
<span id="legitimacyTest"></span>

### bool AbstractExpressionCalculation::legitimacyTest (const QString &input)
对表达式进行合法性检验，所检测错误包括：存在非法字符、运算符错误、括号匹配错误、语法错误以及未知错误，当检测到错误时，将会抛出一个`CalException`型的异常。确保输入的表达式均为合法，保障后续计算能正常运行。

##
<span id="infixToPostfix"></span>

### QQueue<QString\>AbstractExpressionCalculation::infixToPostfix(const QString &input)
将中缀表达式转换成后缀表达式，其中创建了两个栈（存数字栈num和存运算符栈opera）以及一个队列（用于将最终结果反向排列并输出）来实现表达式字符的重排，转换后的后缀表达式保留了原式所有的运算优先级（具体优先级另见[QHash<QChar,int32_t> mOptPriority](#mOptPriority)），确保运算过程、运算结果不发生变化。

举例：

```c++
infixexp = 1+1/4-(5+1)*4;
postfix = QQueue<QString>AbstractExpressionCalculation::infixToPostfix( infixexp );
```

输出结果：

`postfix = 114/+51+4*-+`

##
<span id="postfixEvaluation"></span>

### QString AbstractExpressionCalculation::**postfixEvaluation(QQueue<QString\> input)**
对后缀表达式进行计算，具体运算过程另见:[QString doOperation(const QString &numA,const QString &numB,const QString &opt)][doOperation]并返回计算结果。

举例：

```c++
postfix = 114/+51+4*-+;
answer = QQueue<QString>AbstractExpressionCalculation::infixToPostfix( infixexp );
```

结果：

`answer = 24.75`

##
<span id="startCalculate"></span>

### QString AbstractExpressionCalculation::startCulculate(int32_t *success)

标志着表达式计算的开始，同时该函数会先后调用合法性检验函数、函数识别函数、中缀转后缀函数，以及后缀表达式计算函数。所以在进行计算时仅需调用该函数即可，节省了繁琐且重复的函数调用过程。

##

<span id="isOperator"></span>

**bool AbstractExpressionCalculation::isOperator(const QString &inputalp)=0**

判断表达式中输入字符是否为运算符。在该类中此函数为虚函数。

##

<span id="doOperation"></span>

### QString AbstractExpressionCalculation::doOperation(const QString &numA,const QString &numB,const QString &opt)=0

对后缀表达式栈进行计算，具体过程为：返回值 = 栈顶值 运算符 栈次顶值。其中运算符包括一般运算符与函数运算符。 在该类中此函数为虚函数。

##

<span id="preTreatment"></span>

### void AbstractExpressionCalculation::preTreatment( )

对负数进行预处理，在识别到负数时，该函数会在负数前补充“0”。使负数非负化，减去了表达式计算时对负数的额外处理过程，也对表达式计算速度进行优化。

