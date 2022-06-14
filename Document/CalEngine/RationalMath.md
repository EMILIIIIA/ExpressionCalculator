# [RationalMath](../index.md)
RationalMath提供了高级数学运算功能，例如乘方、开根、log、ln等，且具备高扩展性，能够根据需求添加更多高级运算。

|**头文件**|**#include "CalEngine/RationalMath.h"**|
|----|:-------|

## 公有成员

|返回值/常量类型|函数名/常量名|
|----|:-------|
|**static const Rationa**|**[math_pi](#常量)**|
|**static const Rationa**|**[math_e](#常量)**|
|**static const Rationa**|**[math_ln2](#常量)**|
|**static const Rationa**|**[math_ln5](#常量)**|
|**explicit**|**[RationalMath()](#Rc)**|
|**static Rational**|**[abs(const Rational *&A*)](#abs)**|
|**static Rational**|**[ceil(const Rational *&A*)](#ceil)**|
|**static Rational**|**[floor(const Rational *&A*)](#floor)**|
|**static Rational**|**[pow(const Rational *&A*,int32\_t *n*)](#po)**|
|**static Rational**|**[pow(const Rational *&A*,const Rational *&B*)](#pow)**|
|**static Rational**|**[exp(const Rational *&A*)](#exp)**|
|**static Rational**|**[ln(const Rational *&A*)](#ln)**|
|**static Rational**|**[log(const Rational *&A*,const Rational *&B*)](#log)**|
|**static Rational**|**[sqrt(const Rational *&Base*,const Rational *&Exp*)](#sqrt)**|
|**static Rational**|**[factorial(const Rational *&A*)](#factorial)**|

<span id="常量"></span>

## 常量

|**math_pi**|**圆周率3.14159265358979323846**|
|----|:-------|
|**math_e**|**自然常数2.71828182845904523536**|
|**math_ln2**|**0.69314718055994530941723212145818**|
|**math_ln5**|**1.6094379124341003746007593332262**|

<span id="Rc"></span>

## RationalMath()

默认构造函数

<span id="abs"></span>

## static Rational abs(const Rational *&A*)

获取数字的绝对值

<span id="ceil"></span>

## static Rational ceil(const Rational *&A*)

对数字向上取整

<span id="floor"></span>

## static Rational floor(const Rational *&A*)

对数字向下取整

<span id="ceil"></span>

## static Rational ceil(const Rational *&A*)

对数字向上取整

<span id="po"></span>

## static Rational pow(const Rational *&A*,int32\_t *n*)

仅当幂为整数且大小在`int`范围内时所调用的函数，减少运算量

<span id="pow"></span>

## static Rational pow(const Rational *&A*,const Rational *&B*)

计算`A`的`B`次幂，并返回结果(精度为20)

若幂为整数，则会将`Rational`转换为`int`，后调用[`static Rational pow(const Rational &A,int32_t n)`](#po)进行运算

<span id="exp"></span>

## static Rational exp(const Rational *&A*)

计算`e`的`A`次幂，并返回结果

整数部分调用[`static Rational pow(const Rational &A,const Rational &B)`](#pow)进行运算

小数部分直接调用`qPow`运算

<span id="ln"></span>

## static Rational ln(const Rational *&A*)

计算`lnA`，并返回结果

<span id="log"></span>

## static Rational log(const Rational *&A*,const Rational *&B*)

计算logA(B)，并返回结果

利用换底公式logA(B)=lnB/lnA，后调用[`static Rational ln(const Rational &A)`](#ln)进行计算

<span id="sqrt"></span>

## static Rational sqrt(const Rational *&Base*,const Rational *&Exp*)

计算`Base`的根下`Exp`次方，并返回结果

调用[`static Rational pow(const Rational &A,const Rational &B)`](#pow)进行运算

其中`Exp = 1/B` `Base = A`

<span id="factorial"></span>

## static Rational factorial(const Rational *&A*)

计算A的阶乘，并返回结果
