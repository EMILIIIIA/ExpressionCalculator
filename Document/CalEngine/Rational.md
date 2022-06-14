# [Rational](../index.md)
Rational负责对两数进行基础的数学运算，实现了创建、储存数字、高精度四则运算、重载运算符等功能。

|**头文件**|**#include "CalEngine/Rational.h"**|
|----|:-------|

## 私有成员

|返回值/变量类型|函数名/变量名|
|----|:-------|
|**QVector<int8\_t>**|**[mInteger](#变量)**|
|**QVector<int8\_t>**|**[mDecimal](#变量)**|
|**bool**|**[mSign](#变量)**|
|**int32\_t**|**[mIntergerSize](#变量)**|
|**int32\_t**|**[mDecimalSize](#变量)**|
|**void**|**[deleteLeadingZreo(Rational *&A*)const](#deleteLeadingZreo)**|
|**int8\_t**|**[rationalCompare(const Rational *&A*,const Rational *&B*)const](#rationalCompare)**|
|**void**|**[rationalAdd(const Rational *&A*,const Rational *&B*,Rational *&Res*)const](#rationalAdd)**|
|**void**|**[rationalSubtract(const Rational *&A*,const Rational *&B*,Rational *&Res*)](#rationalSubtract)**|
|**void**|**[rationalMultiply(const Rational *&A*,const Rational *&B*,Rational *&Res*)](#rationalMultiply)**|
|**void**|**[rationalDivide(const Rational *&A*,const Rational *&B*,Rational *&Res*,int32_t *precision*)const](#rationalDivide)**|

## 公有成员

|返回值|函数名|
|:-------|:-------|
|**explicit**|**[Rational()](#Ra)**|
|**explicit**|**[~Rational()](#Rb)**|
|**void**|**[setNumber(const QString *&inputNumber*)](#setNumber)**|
|**bool**|**[hasNumber()](#hasNumber)**|
|**QString**|**[getNumber()const](#getNumber)**|
|**QString**|**[getInteger()const](#getInteger)**|
|**QString**|**[getDecimal()const](#getDecimal)**|
|**Rational**|**[getOppositeNumber()const](#getOppositeNumber)**|
|**void**|**[clearNumber()](#clearNumber)**|
|**void**|**[setOppositeNumber()](#setOppositeNumber)**|
|**void**|**[setPrecision(const int32_t *precision*)](#setPrecision)**|
|**bool**|**[isNegative()const](#isNegative)**|
|**static QVector\<T\>**|**[getReverse(const QVector\<T\> *&A*)](#getReverse)**|
|**bool**|**[operator>(const Rational *&A*)const](#oa)**|
|**bool**|**[operator>=(const Rational *&A*)const](#ob)**|
|**bool**|**[operator<(const Rational *&A*)const](#oc)**|
|**bool**|**[operator<=(const Rational *&A*)const](#od)**|
|**bool**|**[operator==(const Rational *&A*)const](#oe)**|
|**bool**|**[operator!=(const Rational *&A*)const](#of)**|
|**Rational**|**[operator+(const Rational *&A*)const](#og)**|
|**Rational**|**[operator-(const Rational *&A*)const](#oh)**|
|**Rational**|**[operator*(const Rational *&A*)const](#oi)**|
|**Rational**|**[operator/(const Rational *&A*)const](#oj)**|
|**void**|**[operator=(const Rational *&A*)](#ok)**|
|**Rational&**|**[operator=(Rational *&&A*)](#ol)**|
|**QString**|**[operator QString()](#om)**|
|**void**|**[operator+=(const Rational *&A*)](#on)**|
|**void**|**[operator-=(const Rational *&A*)](#oo)**|
|**void**|**[operator*=(const Rational *&A*)](#op)**|
|**void**|**[operator/=(const Rational *&A*)](#oq)**|

<span id="Rational"></span>

## 变量

|**变量名**|含义|
|----|:-------|
|**mInteger**|整数部分 从左往右为个位，十位，百位|
|**mDecimal**|小数部分 从左往右为十分位，百分位，千分位|
|**mSign**|符号 0正1负|
|**mIntegerlSize**|整数部分大小|
|**mDecimalSize**|小数部分大小|

<span id="deleteLeadingZreo"></span>

## void deleteLeadingZreo(Rational *&A*)const

删除指定高精度数的前导零

举例：

```
deleteLeadingZreo(Res);
```

<span id="rationalCompare"></span>

## int8\_t rationalCompare(const Rational *&A*,const Rational *&B*)const

A数>B数 返回`1`

B数>A数 返回`-1`

A数=B数 返回`0`

<span id="rationalAdd"></span>

## void rationalAdd(const Rational *&A*,const Rational *&B*,Rational *&Res*)const

高精度同正同负加法，此函数为几个运算符重载的内部实现

将A\+B的值赋予Res

<span id="rationalSubtract"></span>

## void rationalSubtract(const Rational *&A*,const Rational *&B*,Rational *&Res*)const

高精度同正同负减法，此函数为几个运算符重载的内部实现

将A\-B的值赋予Res

<span id="rationalMultiply"></span>

## void rationalMultiply(const Rational *&A*,const Rational *&B*,Rational *&Res*)const

高精度乘法，此函数为几个运算符重载的内部实现

将A\*B的值赋予Res

<span id="rationalDivide"></span>

## void rationalDivide(const Rational *&A*,const Rational *&B*,Rantional *&Res*,int32_t *precision*)const

高精度除法，此函数为几个运算符重载的内部实现

将A/B的值赋予Res，可以通过设置`precision`来指定运算结果的精度

<span id="Ra"></span>

## Rational

构造函数，提供了多种创建数字的方式

将导入的数据转换成`QString`形式，后交由[`setNumber()`](#setNumber)函数进行处理

### Rational()

创建空数字

### Rational(const Rational *&inputNumber*)

从Rational创建数字

### Rational(const Rational *&&inputNumber*)

移动构造，从Rational创建数字

### Rational(const QString *&inputNumber*)

从字符串创建数字

### Rational(const int32_t *&inputNumber*)

从int32创建数字

### Rational(const long double *&inputNumber*)

从double64创建数字

### Rational(const double *&inputNumber*)

从double创建数字

### Rational(const char\* *inputNumber*)

从char\*创建数字

<span id="Rb"></span>

## ~Rational

析构函数

<span id="setNumber"></span>

## void setNumber(const QString *&inputNumber*)

设置高精度数

将以`QString`形式储存的数字进行拆分，并将其整数与小数部分分别储存于[`mInteger mDecimal`](#变量)中

计算其整数与小数部分大小，分别储存于[`mIntegerSize mDecimalSize`](#变量)中

<span id="hasNumber"></span>

## bool hasNumber()

检查该对象中是否存在高精度数，即[`mInteger mDecimal`](#变量)是否为空

存在 返回`true`

不存在 返回`false`

<span id="getNumber"></span>

## QString getNumber()const

以字符串形式输出储存的高精度数

举例：

```
Rational number(114514);
QString a = number.getNumber();
```

<span id="getInteger"></span>

## QString getInteger()const

单独获取高精度数的整数部分(字符串形式)

<span id="getDecimal"></span>

## QString getDecimal()const

单独获取高精度数的小数部分(字符串形式)

<span id="getOppositeNumber"></span>

## Rational getOppositeNumber()const

调用[`setOppositeNumber()`](#setOppositeNumber)函数进行处理，获取相反数

<span id="clearNumber"></span>

## void clearNumber()

清除储存的数字

<span id="setOppositeNumber"></span>

## void setOppositeNumber()

更改储存数字的符号[`mSign`](#变量)，设置相反数

<span id="setPrecision"></span>

## void setPrecision(const int32\_t *precision*)

设置精度，将超精度小数抛弃、超精度整数置零

<span id="isNegative"></span>

## bool isNegative()const

判断数字正负

正数 返回`0`

负数 返回`1`

<span id="getReverse"></span>

## static QVector<T> getReverse(const QVector<T> *&A*)

生成Vector内元素的倒序序列并返回，方便一些对齐计算

举例：

```
QVector<int8_t> rIntegerA = getReverse(A.mInteger);
```

<span id="oa"></span>

## bool operator>(const Rational *&A*)const

重载大于号，通过调用[`rationalCompare(const Rational &A,const Rational &B)const`](#rationalCompare)函数实现

自身>输入值 返回`true`

否则 返回`false`

举例：

```
Rational num1(114);
Rational num2(514);
bool a = num1>num2;
```

`a`的值为`false`

<span id="ob"></span>

## bool operator>=(const Rational *&A*)const

重载大于等于号

自身>=输入值 返回`true`

否则 返回`false`

<span id="oc"></span>

## bool operator<(const Rational *&A*)const

重载小于号

自身<输入值 返回`true`

否则 返回`false`

<span id="od"></span>

## bool operator<=(const Rational *&A*)const

重载小于等于号

自身<=输入值 返回`true`

否则 返回`false`

<span id="oe"></span>

## bool operator==(const Rational *&A*)const

重载等于号

自身==输入值 返回`true`

否则 返回`false`

<span id="of"></span>

## bool operator!=(const Rational *&A*)const

重载不等于号

自身\!=输入值 返回`true`

否则 返回`false`

<span id="og"></span>

## Rational operator+(const Rational *&A*)const

重载加法，通过调用[`rationalAdd`](#rationalAdd)或[`rationalSubtract`](#rationalSubtract)函数实现

获取两数相加的值，返回一个Rantional类型实例

举例：

```
Rational num1(114);
Rational num2(514);
Rational res(num1+num2);
```
此时`res`中储存的值为628

<span id="oh"></span>

## Rational operator-(const Rational *&A*)const

重载减法

获取两数相减的值，返回一个Rantional类型实例

<span id="oi"></span>

## Rational operator*(const Rational *&A*)const

重载乘法

获取两数相乘的值，返回一个Rantional类型实例

<span id="oj"></span>

## Rational operator/(const Rational *&A*)const

重载除法(默认最高精度20)

获取两数相除的值，返回一个Rantional类型实例

<span id="ok"></span>

## void operator=(const Rational *&A*)const

重载赋值号 深拷贝\
注意：根据编码规范，赋值号应该返回一个引用，但是此函数还未实现

<span id="ol"></span>

## Rational& operator=(const Rational *&&A*)const

重载赋值号 浅拷贝

<span id="om"></span>

## operator QString()

重载强制类型转换运算符`QString`

调用该对象的[`getNumber()`](#getNumber)函数，返回`QString`类型

<span id="on"></span>

## void operator+=(const Rational &A)

重载加等于

举例：

```
Rational num1(114);
Rational num2(514);
num1+=num2
```
此时`num1`中储存的值为628

<span id="oo"></span>

## void operator-=(const Rational &A)

重载减等于

<span id="op"></span>

## void operator*=(const Rational &A)

重载乘等于

<span id="oq"></span>

## void operator/=(const Rational &A)

重载除等于
