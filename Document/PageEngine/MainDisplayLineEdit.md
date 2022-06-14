# [MainDisplayLineEdit](../index.md)
MainDisplayLineEdit是显示表达式的LineEdit控件，负责维护表达式与显示格式。

|**头文件**|**#include "PageEngine/MainDisplayLineEdit.h"**|
|----|:-------|
|**继承自**|**QLineEdit**|

## 公有成员

|**QString**|**[getExpression()](#getExpression)**|
|----|:-------|
|**void**|**[setExpression(const QString &inputExp)](#setExpression)**|
|**void**|**[appendExpression(const QString &willappend)](#appendExpression)**|
|**void**|**[insertExpression(const QString &willappend,const int32_t pos)](#insertExpression)**|
|**void**|**[chopExpression(unsigned int par)](#chopExpression)**|
|**void**|**[clearExpression()](#clearExpression)**|
|**void**|**[removeExpression(const int32_t pos,const int32_t n)](#removeExpression)**|
|**void**|**[changeTextToFormat()](#changeTextToFormat)**|
|**void**|**[setError(const QString &inputExp)](#setError)**|
|**bool**|**[getHasError()](#getHasError)**|

## 私有成员

|**QFont**|**mDispFont**|
|----|:-------|
|**bool**|**mHasError**|
|**bool**|**mIsEmptyExp**|

## 共有槽
|**void**|**[on_linedit_textedited(QString)](#on_linedit_textedited)**|
|----|:-------|

## 详细描述
MainDisplayLineEdit是显示表达式的LineEdit控件，创建并维护了一个表达式。无论是键盘事件输入的字符，还是界面控件按钮输入的字符，都会通过调用setExpression()等函数的方式输入。同时这个函数会记录并且显示计算结果的错误状态，自动调整字号以适应界面大小
## 成员函数文档


<span id="getExpression"></span>
### QString MainDisplayLineEdit::getExpression()
获取当前存储的表达式

##
<span id="setExpression"></span>
### void MainDisplayLineEdit::setExpression(const QString &inputExp)
设置表达式，并且调用changeTextToFormat()函数自动修改表达式格式

##
<span id="appendExpression"></span>
### void MainDisplayLineEdit::appendExpression(const QString &willappend)
在表达式末尾追加字符，并且调用changeTextToFormat()函数自动修改表达式格式

##
<span id="insertExpression"></span>
### void MainDisplayLineEdit::insertExpression(const QString &willappend,const int32_t pos)
在表达式中插入字符，并且调用changeTextToFormat()函数自动修改表达式格式

##
<span id="chopExpression"></span>
### void MainDisplayLineEdit::chopExpression(unsigned int par)
在表达式末尾删除字符，并且调用changeTextToFormat()函数自动修改表达式格式

##
<span id="clearExpression"></span>
### void MainDisplayLineEdit::clearExpression()
清空表达式，并且调用changeTextToFormat()函数自动修改表达式格式

##
<span id="removeExpression"></span>
### void MainDisplayLineEdit::removeExpression(const int32_t pos,const int32_t n)
在表达式中删除字符，并且调用changeTextToFormat()函数自动修改表达式格式

##
<span id="changeTextToFormat"></span>
### void MainDisplayLineEdit::changeTextToFormat()
修改表达式格式，主要有以下几个内容。将空表达式设置为0，在空表达式中追加字符后自动删除0。当被设置为显示错误信息的状态下追加字符时删除错误信息，并且接触错误状态。自动适应屏幕宽度，防止字符超出屏幕范围

##
<span id="setError"></span>
### void MainDisplayLineEdit::setError(const QString &inputExp)
将当前表达式设置为错误状态，并设置错误信息

##
<span id="getHasError"></span>
### void MainDisplayLineEdit::getHasError()
获取当前LineEdit状态，是否是显示报错的状态







