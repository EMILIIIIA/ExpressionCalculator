# [PageManager](../index.md)
PageManager提供了对计算器页面的统一管理，实现批量添加页面、设置页面大小与快速设置焦点等功能。同时此类为QObject，可以使用Qt的内存管理机制。

|**头文件**|**#include "PageEngine/PageManager.h"**|
|----|:-------|
|**继承自**|**QObject**|

## 公有成员

|**explicit**|**[PageManager(QObject *\*parent* = nullptr)](#PageManager)**|
|----|:-------|
|**void**|**[addCalPage(QWidget\* *willadd*, QWidget *\*parent*)](#addCalPage)**|
|**void**|**[setCalPageSize(int32_t *x*, int32_t *y*)](#setCalPageSize)**|
|**void**|**[setCalPageFocus(int32_t *pageIndex*)](#setCalPageFocus)**|
|**QWidget\***|**[getCalPage(int32_t *widgetIndex*)](#getCalPage)**| 

## 私有成员

|**QVector<QWidget\*>**|**mCalPages**|
|----|:-------|
|**QObject**|**\*mParentWindow**|

## 详细描述
在计算器中，有许多个页面，如普通型计算器页面、科学型计算器页面等，这些页面最终都要嵌入主窗口之中。本类旨在简化页面的创建过程，通过使用QVector存储页面指针，统一对页面进行管理。实现批量添加页面、设置页面大小与快速设置焦点等功能。同时此类为QObject，凭借QT强大的内存管理机制，此类实例所属所有子界面实例都会在父实例析构时自动回收内存
## 成员函数文档


<span id="PageManager"></span>
### PageManager::PageManager(QObject *\*parent* = nullptr)
构造函数，将传入的父实例指针记录

举例：
`PageManager pagelist;`

##
<span id="addCalPage"></span>
### void PageManager::addCalPage(QWidget\* *willadd*, QWidget *\*parent*)
向容器内添加页面。接受两个参数，*willadd*为将要添加的页面指针，*\*parent*为这个页面的父页面。需要注意的是，加入容器的页面会自动按先后顺序编号

举例：
`pagelist.addCalPage(new NormalCalPage,ui->NormalCal);`

##
<span id="setCalPageSize"></span>
### void PageManager::setCalPageSize(int32_t *x*, int32_t *y*)
设置所有页面的尺寸。接受两个参数，*x*为宽度，*y*为长度。此函数一般配合resizeEvent()使用

举例：

    void MainWindow::resizeEvent(QResizeEvent *event)
    {
        pagelist.setCalPageSize(ui->width(),ui->height());
    }
另见：[QResizeEvent](https://doc.qt.io/qt-5/qresizeevent.html) [QWidget](https://doc.qt.io/qt-5/qwidget.html)
##
<span id="setCalPageFocus"></span>
### void PageManager::setCalPageFocus(int32_t *pageIndex*)
设置页面焦点，接受一个参数*pageIndex*，将对应编号的页面设置为当前焦点

##
<span id="getCalPage"></span>
### QWidget* PageManager::getCalPage(int32_t *widgetIndex*)
获取页面指针，接受一个参数*widgetIndex*，返回此编号对应页面的指针